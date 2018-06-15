/************************************************************
*                                                           *
*   Bruno Brandão Inácio - NUSP: 9838122                    *
*   Davi José Marques Vieira - NUSP 9838140                 *
*                                                           *
*************************************************************
* src/filtro.c                                              *
*************************************************************
*                                                           *
************************************************************/

#include "filtro.h"

void filtroPassaBaixa(double complex *f, int size, double freqFundamental, double corta) {
    for (int i = 0; i < size; i++) {
        if (i*freqFundamental > corta)
            f[i] = 0.0;
    }
}

void filtroPassaAlta(double complex *f, int size, double freqFundamental, double corta) {
    for (int i = 0; i < size; i++)
        if (i*freqFundamental < corta)
            f[i] = 0.0;
}

void filtroPassaFaixa(double complex *f, int size, double freqFundamental, double freqMin, double freqMax) {
    for (int i = 0; i < size; i++)
        if (i*freqFundamental < freqMin || i*freqFundamental > freqMax)
            f[i] = 0.0;

}

void filtroRejeitaFaixa(double complex *f, int size, double freqFundamental, double freqMin, double freqMax) {
    for (int i = 0; i < size; i++)
        if (i*freqFundamental > freqMin && i*freqFundamental < freqMax)
            f[i] = 0.0;
}
