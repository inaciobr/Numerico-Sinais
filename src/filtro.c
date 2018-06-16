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

/**
 *
 */
void filtroPassaBaixa(double complex *c, int size, double freqFundamental, double corta) {
    int N = size / 2;

    for (int k = 0; k < N; k++)
        if (k*freqFundamental > corta)
            c[k] = c[size - k - 1] = 0.0;
}

/**
 *
 */
void filtroPassaAlta(double complex *c, int size, double freqFundamental, double corta) {
    int N = size / 2;

    for (int k = 0; k < N; k++)
        if (k*freqFundamental < corta)
            c[k] = c[size - k - 1] = 0.0;
}

/**
 *
 */
void filtroPassaFaixa(double complex *c, int size, double freqFundamental, double freqMin, double freqMax) {
    int N = size / 2;

    for (int k = 0; k < N; k++)
        if (k*freqFundamental < freqMin || k*freqFundamental > freqMax)
            c[k] = c[size - k - 1] = 0.0;

}

/**
 *
 */
void filtroRejeitaFaixa(double complex *c, int size, double freqFundamental, double freqMin, double freqMax) {
    int N = size / 2;

    for (int k = 0; k < N; k++)
        if (k*freqFundamental > freqMin && k*freqFundamental < freqMax)
            c[k] = c[size - k - 1] = 0.0;
}

/**
 *
 */
void filtroAmplitudePassaAlta(double complex *c, int size, double ampMin) {
    int N = size / 2;

    for (int k = 0; k < N; k++)
        if (2*cabs(c[k]) < ampMin)
            c[k] = c[size - k - 1] = 0.0;
}

/**
 *
 */
void compressaoAudicaoHumana(double complex *c, int size, double freqFundamental, double ampMin) {
    filtroPassaFaixa(c, size, freqFundamental, 20, 20E3);
    filtroAmplitudePassaAlta(c, size, ampMin);
}
