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
    double complex *cChannel1, *cChannel2;
    channels2Complex (sox.numSamples, sox.channel1, sox.channel2, &cChannel1, &cChannel2);

    soundFrequency frequency;
    frequency.size = sox.numSamples;
    frequency.frequency = sox.sampleRate;
    frequency.channel1 = fftDireta(cChannel1, sox.numSamples);
    frequency.channel2 = cChannel2 == NULL ? NULL : fftDireta(cChannel2, sox.numSamples);

    free(cChannel1);
    if (cChannel2 != NULL)
        free(cChannel2);

    return frequency;
}

soundData frequency2SoX(soundFrequency frequency) {
    double complex *cChannel1, *cChannel2;

    soundData sox;
    sox.sampleRate = frequency.frequency;
    sox.channels = frequency.channel2 == NULL ? 1 : 2;
    sox.duration = (double) frequency.frequency / frequency.frequency;
    sox.numSamples = frequency.size;

    cChannel1 = fftInversa(frequency.channel1, frequency.size);
    cChannel2 = frequency.channel2 == NULL ? NULL : fftInversa(frequency.channel2, frequency.size);
    complex2channels(frequency.size, cChannel1, cChannel2, &sox.channel1, &sox.channel2);

    free(cChannel1);
    if (cChannel2 != NULL)
        free(cChannel2);

    return sox;
}

void channels2Complex(int size, double *channel1, double *channel2, double complex **cChannel1, double complex **cChannel2) {
    *cChannel1 = malloc(size * sizeof(double complex));
    *cChannel2 = channel2 == NULL ? NULL : malloc(size * sizeof(double complex));

    for (int i = 0; i < size; i++) {
        (*cChannel1)[i] = channel1[i];

        if (channel2 != NULL)
            (*cChannel2)[i] = channel2[i];
    }
}

void complex2channels(int size, double complex *cChannel1, double complex *cChannel2, double **channel1, double **channel2) {
    *channel1 = malloc(size * sizeof(double));
    *channel2 = cChannel2 == NULL ? NULL : malloc(size * sizeof(double));

    for (int i = 0; i < size; i++) {
        (*channel1)[i] = creal(cChannel1[i]);

        if (cChannel2 != NULL)
            (*channel2)[i] = creal(cChannel2[i]);
    }
}
