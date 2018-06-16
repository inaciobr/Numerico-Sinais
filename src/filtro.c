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
    if (c == NULL)
        return;

    int N = size / 2;

    for (int k = 0; k < N; k++)
        if (k*freqFundamental > corta)
            c[k] = c[size - k - 1] = 0.0;
}

/**
 *
 */
void filtroPassaAlta(double complex *c, int size, double freqFundamental, double corta) {
    if (c == NULL)
        return;

    int N = size / 2;

    for (int k = 0; k < N; k++)
        if (k*freqFundamental < corta)
            c[k] = c[size - k - 1] = 0.0;
}

/**
 *
 */
void filtroPassaFaixa(double complex *c, int size, double freqFundamental, double freqMin, double freqMax) {
    if (c == NULL)
        return;

    int N = size / 2;

    for (int k = 0; k < N; k++)
        if (k*freqFundamental < freqMin || k*freqFundamental > freqMax)
            c[k] = c[size - k - 1] = 0.0;

}

/**
 *
 */
void filtroRejeitaFaixa(double complex *c, int size, double freqFundamental, double freqMin, double freqMax) {
    if (c == NULL)
        return;

    int N = size / 2;

    for (int k = 0; k < N; k++)
        if (k*freqFundamental > freqMin && k*freqFundamental < freqMax)
            c[k] = c[size - k - 1] = 0.0;
}

/**
 *
 */
double compressaoRemoveAmplitude(double complex *c, int size, double ampMin) {
    if (c == NULL)
        return;

    int N = size / 2;
    int zeros = 0;

    for (int k = 0; k < N; k++) {
        if (cabs(c[k]) && 2*cabs(c[k]) < ampMin) {
            c[k] = c[size - k - 1] = 0.0;
            zeros++;
        }
    }

    return (double) zeros / size;
}
