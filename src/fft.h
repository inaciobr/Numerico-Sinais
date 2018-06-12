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
#include <stdlib.h>

#define PI  3.14159265358979323846

void fftDireta(double complex *F, double complex *ck, int nTermos);
void fftInversa(double complex *F, double complex *ck, int nTermos);

#endif // SOUDDATA_H_INCLUDED
