/************************************************************
*                                                           *
*   Bruno Brandão Inácio - NUSP: 9838122                    *
*   Davi José Marques Vieira - NUSP 9838140                 *
*                                                           *
*************************************************************
* src/soundData.h                                           *
************************************************************/

#ifndef SOUDDATA_H_INCLUDED
#define SOUDDATA_H_INCLUDED

#include <stdio.h>

typedef struct {
    int sampleRate;
    int channels;

    double duration;

    int numSamples;
    double *ch1;
    double *ch2;
} soundData;

soundData readSoX(char file[]);
void writeSoX(char file[], soundData sox);
void freeSoX(soundData *sox);

int numberOfLines (char file[]);

#endif // SOUDDATA_H_INCLUDED
