/************************************************************
*                                                           *
*   Bruno Brandão Inácio - NUSP: 9838122                    *
*   Davi José Marques Vieira - NUSP 9838140                 *
*                                                           *
*************************************************************
* src/soundFrequency.c                                      *
*************************************************************
*                                                           *
************************************************************/

#include "soundFrequency.h"

soundFrequency SoX2Frequency(soundData sox) {
    double complex *complexChannel = malloc(sox.numSamples * sizeof(double complex));
    soundFrequency frequency;

    frequency.size = sox.numSamples;
    frequency.sampleRate = sox.sampleRate;
    frequency.frequency = (double) sox.sampleRate / sox.numSamples;


    frequency.channel1 = malloc(sox.numSamples * sizeof(double complex));
    double2complex(sox.channel1, complexChannel, sox.numSamples);
    //fftDireta(complexChannel, frequency.channel1, frequency.size);
    fft2(frequency.channel1, complexChannel, frequency.size, 1);

    if (sox.channels == 2) {
        frequency.channel2 = malloc(sox.numSamples * sizeof(double complex));
        double2complex(sox.channel2, complexChannel, sox.numSamples);
        //fftDireta(complexChannel, frequency.channel2, frequency.size);
        fft2(frequency.channel2, complexChannel, frequency.size, 1);
    } else {
        frequency.channel2 = NULL;
    }

    free(complexChannel);

    return frequency;
}

soundData frequency2SoX(soundFrequency frequency) {
    double complex *complexChannel = malloc(frequency.size * sizeof(double complex));
    soundData sox;

    sox.numSamples = frequency.size;
    sox.sampleRate = frequency.sampleRate;
    sox.channels = frequency.channel2 == NULL ? 1 : 2;
    sox.duration = (double) sox.numSamples / sox.sampleRate;

    sox.channel1 = malloc(frequency.size * sizeof(double));
    //fftInversa(complexChannel, frequency.channel1, frequency.size);
    fft2(complexChannel, frequency.channel1, frequency.size, 0);
    complex2double(complexChannel, sox.channel1, frequency.size);

    if (sox.channels == 2) {
        sox.channel2 = malloc(frequency.size * sizeof(double));
        //fftInversa(complexChannel, frequency.channel2, frequency.size);
        fft2(complexChannel, frequency.channel2, frequency.size, 0);
        complex2double(complexChannel, sox.channel2, frequency.size);
    } else {
        sox.channel2 = NULL;
    }

    free(complexChannel);

    return sox;
}

void double2complex(double *channel, double complex *cChannel, int size) {
    for (int i = 0; i < size; i++)
        cChannel[i] = channel[i];
}

void complex2double(double complex *cChannel, double *channel, int size) {
    for (int i = 0; i < size; i++)
        channel[i] = creal(cChannel[i]);
}
