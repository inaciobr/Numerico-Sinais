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

typedef struct {
    double frequency;

    int size;
    complex double *cAmplitude;
} soundFrequency;

soundFrequency SoX2Frequency();

void channels2Complex(int size, double *ch1, double *ch2, double complex **cCh1, double complex **cCh2);

#endif // SOUDDATA_H_INCLUDED
