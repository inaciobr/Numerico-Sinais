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
    double frequency;
    int sampleRate;
    int numSamples;
    int sizeChannel;
    double compressionRate;

    complex double *channel1;
    complex double *channel2;
} soundFrequency;

soundFrequency SoX2Frequency(soundData sox, void (*fft)(complex *, complex *, int));
soundData frequency2SoX(soundFrequency frequency, void (*fft)(complex *, complex *, int));

void double2complex(double *channel, double complex *cChannel, int size) ;
void complex2double(double complex *cChannel, double *channel, int size) ;

#endif // SOUNDFREQUENCY_H_INCLUDED
