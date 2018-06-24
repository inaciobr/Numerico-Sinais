/************************************************************
*                                                           *
*   Bruno Brandão Inácio - NUSP: 9838122                    *
*   Davi José Marques Vieira - NUSP 9838140                 *
*                                                           *
*************************************************************
* src/filtro.c                                              *
*************************************************************
* Funções relacionadas a filtragem de frequências.          *
************************************************************/

#include "filtro.h"

/**
 *
 *
 */
void filtroPassaBaixa(double complex *c, int size, double indexMax) {
    if (c == NULL)
        return;

    int N = size / 2;

    for (int k = 0; k < N; k++)
        if (k > indexMax)
            c[k] = c[size - k - 1] = 0.0;
}

/**
 *
 *
 */
void filtroPassaAlta(double complex *c, int size, double indexMin) {
    if (c == NULL)
        return;

    int N = size / 2;

    /* Não corta a frequência de índice zero, associada ao termo constante. */
    for (int k = 1; k < N; k++)
        if (k < indexMin)
            c[k] = c[size - k - 1] = 0.0;
}

/**
 *
 *
 */
void filtroPassaFaixa(double complex *c, int size, double indexMin, double indexMax) {
    if (c == NULL)
        return;

    int N = size / 2;

    for (int k = 0; k < N; k++)
        if (k < indexMin || k > indexMax)
            c[k] = c[size - k - 1] = 0.0;
}

/**
 *
 *
 */
void filtroRejeitaFaixa(double complex *c, int size, double indexMin, double indexMax) {
    if (c == NULL)
        return;

    int N = size / 2;

    for (int k = 0; k < N; k++)
        if (k > indexMin && k < indexMax)
            c[k] = c[size - k - 1] = 0.0;
}

/**
 *
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

    return (double) zeros / N;
}
