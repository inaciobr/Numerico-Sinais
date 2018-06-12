/************************************************************
*                                                           *
*   Bruno Brand�o In�cio - NUSP: 9838122                    *
*   Davi Jos� Marques Vieira - NUSP 9838140                 *
*                                                           *
*************************************************************
* src/soundData.h                                           *
************************************************************/

#ifndef SOUNDDATA_H_INCLUDED
#define SOUNDDATA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int sampleRate;
    int channels;

    double duration;

    int numSamples;
    double *channel1;
    double *channel2;
} soundData;

soundData readSoX(char file[]);
void writeSoX(char file[], soundData sox);
void freeSoX(soundData *sox);

int numberOfLines (char file[]);

#endif // SOUDDATA_H_INCLUDED
