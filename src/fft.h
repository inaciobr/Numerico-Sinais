/************************************************************
*                                                           *
*   Bruno Brandão Inácio - NUSP: 9838122                    *
*   Davi José Marques Vieira - NUSP 9838140                 *
*                                                           *
*************************************************************
* src/fft.h                                                 *
************************************************************/

#ifndef FFT_H_INCLUDED
#define FFT_H_INCLUDED

#include <complex.h>
#include <math.h>
#include <stdlib.h>

#include "fftpack4.h"
#include "soundFrequency.h"

#define PI  3.14159265358979323846

void fftDireta(double complex *c, double complex *F, int nTermos);
void fftInversa(double complex *F, double complex *c, int nTermos);

void fftRecursivaDireta(double complex *c, double complex *f,  int nTermos);
void fftRecursivaInversa(double complex *f, double complex *c,  int nTermos);
void fftrec(double complex *c, double complex *f,  int nTermos, int dir);

void fftpack4Direta(complex *c, complex *f, int nTermos);
void fftpack4Inversa(complex *f, complex *c, int nTermos);

#endif // SOUDDATA_H_INCLUDED
