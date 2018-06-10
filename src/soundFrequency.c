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
#include "soundData.h"
#include "fft.h"

soundFrequency SoX2Frequency(soundData sox) {
    double complex *cCh1, *cCh2;
    channels2Complex (sox.numSamples, sox.ch1, sox.ch2, &cCh1, &cCh2);

    soundFrequency frequency;
    frequency.size = sox.numSamples;
    frequency.cAmplitude = fftDireta(cCh1, sox.numSamples);

    free(cCh1);
    if (cCh2 != NULL)
        free(cCh2);

    return frequency;
}

void channels2Complex(int size, double *ch1, double *ch2, double complex **cCh1, double complex **cCh2) {
    *cCh1 = malloc(size * sizeof(double complex));
    *cCh2 = ch2 == NULL ? NULL : malloc(size * sizeof(double complex));

    for (int i = 0; i < size; i++) {
        (*cCh1)[i] = ch1[i];

        if (ch2 != NULL)
            (*cCh2)[i] = ch2[i];
    }
}
