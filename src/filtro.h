/************************************************************
*                                                           *
*   Bruno Brandão Inácio - NUSP: 9838122                    *
*   Davi José Marques Vieira - NUSP 9838140                 *
*                                                           *
*************************************************************
* src/filtro.h                                              *
************************************************************/

#ifndef FILTRO_H_INCLUDED
#define FILTRO_H_INCLUDED

#include <stdlib.h>
#include <complex.h>

void filtroPassaBaixa(double complex *c, int size, double indexMax);
void filtroPassaAlta(double complex *c, int size, double indexMin);

void filtroPassaFaixa(double complex *c, int size, double indexMin, double indexMax);
void filtroRejeitaFaixa(double complex *c, int size, double indexMin, double indexMax);

void compressaoAudicaoHumana(double complex *c, int size, double freqFundamental, double ampMin);

#endif // FILTRO_H_INCLUDED
