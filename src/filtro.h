/************************************************************
*                                                           *
*   Bruno Brand�o In�cio - NUSP: 9838122                    *
*   Davi Jos� Marques Vieira - NUSP 9838140                 *
*                                                           *
*************************************************************
* src/filtro.h                                              *
************************************************************/

#ifndef FILTRO_H_INCLUDED
#define FILTRO_H_INCLUDED

#include <complex.h>
#include "fft.h"

void filtroPassaBaixa(double complex *f, int size, double freqFundamental, double corta);
void filtroPassaAlta(double complex *f, int size, double freqFundamental, double corta);

void filtroPassaFaixa(double complex *f, int size, double freqFundamental, double freqMin, double freqMax);
void filtroRejeitaFaixa(double complex *f, int size, double freqFundamental, double freqMin, double freqMax);

#endif // FILTRO_H_INCLUDED
