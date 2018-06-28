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
 * NESTA FUNÇÃO, ZERAM-SE TODAS OS SINAIS DE TRANSFORMADA ACIMA DO
 * PARÂMETRO DADO
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
 * NESTA FUNÇÃO, ZERAM-SE TODAS OS SINAIS DE TRANSFORMADA ABAIXO DO
 * PARÂMETRO DADO
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
 * FORA DE UM INTERVALO ESTIPULADO, TODAS OS REPRESENTANTES DESSAS
 * FREQUÊNCIAS SÃO ANULADOS
 */
void filtroPassaFaixa(double complex *c, int size, double indexMin, double indexMax) {
    if (c == NULL)
        return;

    int N = size / 2;

    /* Não corta a frequência de índice zero, associada ao termo constante. */
    for (int k = 1; k < N; k++)
        if (k < indexMin || k > indexMax)
            c[k] = c[size - k - 1] = 0.0;
}

/**
 * DENTRO DE UM INTERVALO ESTIPULADO, TODAS OS REPRESENTANTES DESSAS
 * FREQUÊNCIAS SÃO ANULADOS
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
 * Remove frequências abaixo de uma amplitude mínima ampMin para
 * realizar a compressão do sinal. A função retorna a taxa de
 * compressão.
 */
double compressaoRemoveAmplitude(double complex *c, int size, double ampMin) {
    if (c == NULL)
        return 0.0;

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
