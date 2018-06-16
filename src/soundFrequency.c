/************************************************************
*                                                           *
*   Bruno Brand�o In�cio - NUSP: 9838122                    *
*   Davi Jos� Marques Vieira - NUSP 9838140                 *
*                                                           *
*************************************************************
* src/soundFrequency.c                                      *
*************************************************************
*                                                           *
************************************************************/

#include "soundFrequency.h"

/**
 *
 */
soundFrequency SoX2FrequencyDireta(soundData sox) {
    return SoX2Frequency(sox, &fftDireta);
}

/**
 *
 */
soundFrequency SoX2FrequencyRecursiva(soundData sox) {
    return SoX2Frequency(sox, &fftRecursivaDireta);
}

/**
 *
 */
soundFrequency SoX2Frequency(soundData sox, void (*fft)(complex *, complex *, int)) {
    double complex *complexChannel = malloc(sox.numSamples * sizeof(double complex));
    soundFrequency frequency;

    frequency.size = sox.numSamples;
    frequency.sampleRate = sox.sampleRate;
    frequency.frequency = (double) sox.sampleRate / sox.numSamples;


    frequency.channel1 = malloc(sox.numSamples * sizeof(double complex));
    double2complex(sox.channel1, complexChannel, sox.numSamples);
    fft(frequency.channel1, complexChannel, frequency.size);

    if (sox.channels == 2) {
        frequency.channel2 = malloc(sox.numSamples * sizeof(double complex));
        double2complex(sox.channel2, complexChannel, sox.numSamples);
        fft(frequency.channel2, complexChannel, frequency.size);
    } else {
        frequency.channel2 = NULL;
    }

    free(complexChannel);

    return frequency;
}

/**
 *
 */
soundData frequency2SoXDireta(soundFrequency frequency) {
    return frequency2SoX(frequency, &fftInversa);
}

/**
 *
 */
soundData frequency2SoXRecursiva(soundFrequency frequency) {
    return frequency2SoX(frequency, &fftRecursivaInversa);
}

/**
 *
 */
soundData frequency2SoX(soundFrequency frequency, void (*fft)(complex *, complex *, int)) {
    double complex *complexChannel = malloc(frequency.size * sizeof(double complex));
    soundData sox;

    sox.numSamples = frequency.size;
    sox.sampleRate = frequency.sampleRate;
    sox.channels = frequency.channel2 == NULL ? 1 : 2;
    sox.duration = (double) sox.numSamples / sox.sampleRate;

    sox.channel1 = malloc(frequency.size * sizeof(double));
    fft(complexChannel, frequency.channel1, frequency.size);
    complex2double(complexChannel, sox.channel1, frequency.size);

    if (sox.channels == 2) {
        sox.channel2 = malloc(frequency.size * sizeof(double));
        fft(complexChannel, frequency.channel2, frequency.size);
        complex2double(complexChannel, sox.channel2, frequency.size);
    } else {
        sox.channel2 = NULL;
    }

    free(complexChannel);

    return sox;
}

/**
 *
 */
void double2complex(double *channel, double complex *cChannel, int size) {
    for (int i = 0; i < size; i++)
        cChannel[i] = channel[i];
}

/**
 *
 */
void complex2double(double complex *cChannel, double *channel, int size) {
    for (int i = 0; i < size; i++)
        channel[i] = creal(cChannel[i]);
}
