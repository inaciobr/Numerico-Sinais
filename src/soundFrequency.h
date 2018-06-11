/************************************************************
*                                                           *
*   Bruno Brandão Inácio - NUSP: 9838122                    *
*   Davi José Marques Vieira - NUSP 9838140                 *
*                                                           *
*************************************************************
* src/soundFrequency.h                                      *
************************************************************/

#ifndef SOUNDFREQUENCY_H_INCLUDED
#define SOUNDFREQUENCY_H_INCLUDED

#include <complex.h>
#include <stdlib.h>

#include "soundData.h"
#include "fft.h"

typedef struct {
    int frequency;

    int size;
    complex double *channel1;
    complex double *channel2;
} soundFrequency;

soundFrequency SoX2Frequency(soundData sox);
soundData frequency2SoX(soundFrequency frequency);

void channels2Complex(int size, double *ch1, double *ch2, double complex **cCh1, double complex **cCh2);
void complex2channels(int size, double complex *cChannel1, double complex *cChannel2, double **channel1, double **channel2);

#endif // SOUDDATA_H_INCLUDED
