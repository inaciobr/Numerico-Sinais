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

void double2complex(double *channel, double complex *cChannel, int size) ;
void complex2double(double complex *cChannel, double *channel, int size) ;

#endif // SOUDDATA_H_INCLUDED
