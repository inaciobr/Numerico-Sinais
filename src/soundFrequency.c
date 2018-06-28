/************************************************************
*                                                           *
*   Bruno Brandão Inácio - NUSP: 9838122                    *
*   Davi José Marques Vieira - NUSP 9838140                 *
*                                                           *
*************************************************************
* src/soundFrequency.c                                      *
*************************************************************
* Funções relacionadas ao tratamento de dados de um arquivo *
* de som no domínio da frequência.                          *
************************************************************/

#include "soundFrequency.h"

/**
 * Função para realizar a conversão do tipo soundData, no domínio do tempo
 * para o tipo soundFrequency, no domínimo da frequência complexa.
 * A função recebe como argumento qual fft direta será utilizada.
 */
soundFrequency SoX2Frequency(soundData sox, void (*fft)(complex *, complex *, int)) {
    soundFrequency frequency;

    frequency.sizeChannel = sox.sizeChannel;
    frequency.numSamples = sox.numSamples;
    frequency.sampleRate = sox.sampleRate;
    frequency.frequency = (double) sox.sampleRate / sox.sizeChannel;
    frequency.compressionRate = 0.0;

    double complex *complexChannel = malloc(frequency.sizeChannel * sizeof(double complex));
    frequency.channel1 = malloc(frequency.sizeChannel * sizeof(double complex));
    double2complex(sox.channel1, complexChannel, frequency.sizeChannel);
    fft(frequency.channel1, complexChannel, frequency.sizeChannel);

    if (sox.channels == 2) {
        frequency.channel2 = malloc(frequency.sizeChannel * sizeof(double complex));
        double2complex(sox.channel2, complexChannel, frequency.sizeChannel);
        fft(frequency.channel2, complexChannel, frequency.sizeChannel);
    } else {
        frequency.channel2 = NULL;
    }

    free(complexChannel);

    return frequency;
}

/**
 * Função para realizar a conversão do tipo soundFrequency, no domínimo da
 * frequência complexa para o soundData, no domínio do tempo.
 * A função recebe como argumento qual fft inversa será utilizada.
 */
soundData frequency2SoX(soundFrequency frequency, void (*fft)(complex *, complex *, int)) {
    soundData sox;

    sox.numSamples = frequency.numSamples;
    sox.sizeChannel = frequency.sizeChannel;
    sox.sampleRate = frequency.sampleRate;
    sox.channels = frequency.channel2 == NULL ? 1 : 2;
    sox.duration = (double) sox.numSamples / sox.sampleRate;

    double complex *complexChannel = malloc(frequency.sizeChannel * sizeof(double complex));
    sox.channel1 = malloc(frequency.sizeChannel * sizeof(double));
    fft(complexChannel, frequency.channel1, frequency.sizeChannel);
    complex2double(complexChannel, sox.channel1, frequency.sizeChannel);

    if (sox.channels == 2) {
        sox.channel2 = malloc(frequency.sizeChannel * sizeof(double));
        fft(complexChannel, frequency.channel2, frequency.sizeChannel);
        complex2double(complexChannel, sox.channel2, frequency.sizeChannel);
    } else {
        sox.channel2 = NULL;
    }

    free(complexChannel);

    return sox;
}

/**
 * Função para realizar a conversão de valores do tipo double para o tipo double complex.
 */
void double2complex(double *channel, double complex *cChannel, int size) {
    for (int i = 0; i < size; i++)
        cChannel[i] = channel[i];
}

/**
 * Função para realizar a conversão de valores do tipo double complex para o tipo double.
 */
void complex2double(double complex *cChannel, double *channel, int size) {
    for (int i = 0; i < size; i++)
        channel[i] = creal(cChannel[i]);
}

/**
 * Armazena em um arquivo dados referentes ao sinal no domínio da frequência.
 */
void writeFrequency(char file[], soundFrequency frequency) {
    FILE *fp = fopen(file, "w");

    fprintf(fp, "; Sample Rate %d\n", frequency.sampleRate);
    fprintf(fp, "; Channels %d\n", frequency.channel2 == NULL ? 1 : 2);
    fprintf(fp, "; Duration %f\n", 1./frequency.frequency);
    fprintf(fp, "; Compression rate %.3f%%\n", frequency.compressionRate * 100.0);


    /* Vetor de frequências. */
    double freq = 0.0;
    fprintf(fp, "; f = [");
    for (int i = 0; i < frequency.sizeChannel/2 - 1; i++) {
        fprintf(fp, "%.8g, ", freq);
        freq += frequency.frequency;
    }
    fprintf(fp, "%.8g]\n", freq);

    /* Vetor de amplitudes no canal 1. */
    fprintf(fp, "; A1 = [");
    for (int i = 0; i < frequency.sizeChannel/2 - 1; i++) {
        fprintf(fp, "%.8g, ", 2*cabs(frequency.channel1[i]));
    }
    fprintf(fp, "\%.8g]\n", 2*cabs(frequency.channel1[frequency.sizeChannel/2 - 1]));

    /* Vetor de amplitudes no canal 2. */
    if (frequency.channel2 != NULL) {
        fprintf(fp, "; A2 = [");
        for (int i = 0; i < frequency.sizeChannel/2 - 1; i++) {
            fprintf(fp, "%.8g, ", 2*cabs(frequency.channel2[i]));
        }
        fprintf(fp, "%.8g]\n", 2*cabs(frequency.channel2[frequency.sizeChannel/2 - 1]));
    }


    fclose(fp);
}
