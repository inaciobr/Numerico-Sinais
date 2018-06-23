/************************************************************
*                                                           *
*   Bruno Brandão Inácio - NUSP: 9838122                    *
*   Davi José Marques Vieira - NUSP 9838140                 *
*                                                           *
*************************************************************
* src/soundData.h                                           *
************************************************************/

#ifndef SOUNDDATA_H_INCLUDED
#define SOUNDDATA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "fft.h"

typedef struct {
    int sampleRate;
    int channels;

    double duration;

    int numSamples;
    int sizeChannel;
    double *channel1;
    double *channel2;
} soundData;

soundData readSoX(char file[], int power2);
void writeSoX(char file[], soundData sox);
void freeSoX(soundData *sox);

int numberOfLines (char file[]);
double calculaMedia(double *f, int nTermos);
int nearestPower2(int N);
void completaPotencia2(double *F, int tamanhoAntigo, int tamanhoNovo);

#endif // SOUNDDATA_H_INCLUDED
