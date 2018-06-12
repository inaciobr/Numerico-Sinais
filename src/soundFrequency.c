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

soundFrequency SoX2Frequency(soundData sox) {
    double complex *complexChannel = malloc(sox.numSamples * sizeof(double complex));
    soundFrequency frequency;

    frequency.size = sox.numSamples;
    frequency.frequency = sox.sampleRate;

    frequency.channel1 = malloc(sox.numSamples * sizeof(double complex));
    double2complex(sox.channel1, complexChannel, sox.numSamples);
    fftDireta(complexChannel, frequency.channel1, frequency.size);

    if (sox.channels == 2) {
        frequency.channel2 = malloc(sox.numSamples * sizeof(double complex));
        double2complex(sox.channel2, complexChannel, sox.numSamples);
        fftDireta(complexChannel, frequency.channel2, frequency.size);
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
    sox.sampleRate = frequency.frequency;
    sox.channels = frequency.channel2 == NULL ? 1 : 2;
    sox.duration = (double) frequency.size / frequency.frequency;

    sox.channel1 = malloc(frequency.size * sizeof(double));
    fftInversa(complexChannel, frequency.channel1, frequency.size);
    complex2double(complexChannel, sox.channel1, frequency.size);

    if (sox.channels == 2) {
        sox.channel2 = malloc(frequency.size * sizeof(double));
        fftInversa(complexChannel, frequency.channel2, frequency.size);
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
