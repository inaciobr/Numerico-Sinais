/************************************************************
*                                                           *
*   Bruno Brandão Inácio - NUSP: 9838122                    *
*   Davi José Marques Vieira - NUSP 9838140                 *
*                                                           *
*************************************************************
* src/fft.c                                                 *
*************************************************************
* Funções relacionadas à Transformada de Fourier.           *
************************************************************/

#include "fft.h"

/**
 * 2N = nTermos
 * NESTA SE DA O PROCESSO INVERSO DA FFT, TEM COMO PARÂMETRO O VETOR REAL
 * DE APLITUDES E, APLICANDO O ALGORITMO DADO NO ROTEIRO, VOLTA PARA O VETOR
 * COMPLEXO DA TRANSFORMADA
 */
void fftDireta(double complex *c, double complex *F, int nTermos) {
    double complex odd, even, fase;
    int N = nTermos / 2;

    for (int k = 0; k < N; k++) {
        odd = even = 0.0;

        for (int j = 0; j < N; j++) {
            fase = cexp(-1i * k * PI * j / (N/2));
            even += F[2*j] * fase;
            odd += F[2*j + 1] * fase;
        }

        odd *= cexp(-1i * k * PI / N);

        c[k] = (even + odd) / nTermos;
        c[k + N] = (even - odd) / nTermos;
    }
}

/**
 * NESTA SE DA O PROCESSO INVERSO DA FFT, TEM COMO PARÂMETRO O VETOR COMPLEXO
 * DA TRANSFORMADA E, APLICANDO O ALGORITMO DADO NO ROTEIRO, VOLTA PARA O VETOR
 * REAL DE AMPLITUDE
 */
void fftInversa(double complex *F, double complex *c, int nTermos) {
    double complex odd, even, fase;
    int N = nTermos / 2;

    for (int j = 0; j < N; j++) {
        odd = even = 0.0;

        for (int k = 0; k < N; k++) {
            fase = cexp(1i * k * PI * j / (N/2));
            even += c[2*k] * fase;
            odd += c[2*k + 1] * fase;
        }

        odd *= cexp(1i * j * PI / N);

        F[j] = (even + odd);
        F[j + N] = (even - odd);
    }
}

/**
 * UTILIZANDO  A RECURSIVA DADA, NESTA FUNÇÃO TÊM-SE A OPÇÃO
 * DE SE CHAMAR A SUA FORMA DIRETA
 */
void fftRecursivaDireta(double complex *c, double complex *f, int nTermos) {
    fftrec(c, f, nTermos, 1);

    for (int i = 0; i < nTermos; i++)
        c[i] /= nTermos;
}

/**
 * UTILIZANDO  A RECURSIVA DADA, NESTA FUNÇÃO TÊM-SE A OPÇÃO
 * DE SE CHAMAR A SUA FORMA INVERSA
 */
void fftRecursivaInversa(double complex *f, double complex *c, int nTermos) {
    fftrec(f, c, nTermos, 0);
}

/**
 * AQUI SE APLICA O ALGORITMO RECURSIVO DADO NO ROTEIRO
 */
void fftrec(double complex *c, double complex *f, int nTermos, int dir) {
    int N = nTermos / 2;

    if (N == 1){
        c[0] = f[0] + f[1];
        c[1] = f[0] - f[1];

        return;
    }

    double complex *even = calloc(N, sizeof(double complex));
    double complex *odd = calloc(N, sizeof(double complex));
    double complex *fe = calloc(N, sizeof(double complex));
    double complex *fo = calloc(N, sizeof(double complex));

    for (int j = 0; j < N; j++) {
        fe[j] = f[2*j];
        fo[j] = f[2*j + 1];
    }

    fftrec(even, fe, N, dir);
    fftrec(odd, fo, N, dir);

    double complex eij;
    for (int j = 0; j < N; j++) {
        eij = cexp((dir ? -1i : 1i) * j * PI / N);

        c[j] = even[j] + eij*odd[j];
        c[j + N] = even[j] - eij*odd[j];
    }

    free(even);
    free(odd);
    free(fe);
    free(fo);
}

/**
 * NESTA FUNÇÃO, COM BASE NO LINK DADO PARA A FFTPACK4, PODE-SE CALCULAR
 * A TRANSFORMADA DE UM MANEIRA MUITO OTIMIZADA
 */
void fftpack4Direta(complex *c, complex *f, int nTermos) {
    double *wSave = (double *) malloc((3*nTermos + 15) * sizeof (double));
    int *iFac = (int *) malloc(32 * sizeof(int));
    ezffti(&nTermos, wSave, iFac);

    int N = nTermos / 2;
    double aZero;
    double *x = (double *) malloc(nTermos * sizeof(double));
    double *a = (double *) malloc(N * sizeof(double));
    double *b = (double *) malloc(N * sizeof(double));

    complex2double(f, x, nTermos);
    ezfftf (&nTermos, x, &aZero, a, b, wSave, iFac);


    c[0] = aZero;
    c[N] = a[N - 1];

    for (int i = 0; i < N - 1; i++) {
        c[i + 1] = (a[i] - 1i*b[i]) / 2.0;
        c[2*N - i - 1] = (a[i] + 1i*b[i]) / 2.0;
    }

    free(a);
    free(b);
    free(iFac);
    free(wSave);
    free(x);
}

/**
 * NESTA FUNÇÃO, COM BASE NO LINK DADO PARA A FFTPACK4, PODE-SE CALCULAR
 * O VETOR NO DOMINIO DO TEMPO DE UM MANEIRA MUITO OTIMIZADA,A PARTIR DA
 * TRANSFORMADA DESSE SINAL
 */
void fftpack4Inversa(complex *f, complex *c, int nTermos) {
    double *wSave = (double *) malloc((3*nTermos + 15) * sizeof (double));
    int *iFac = (int *) malloc(32 * sizeof(int));
    ezffti(&nTermos, wSave, iFac);

    int N = nTermos / 2;
    double aZero;
    double *x = (double *) malloc(nTermos * sizeof(double));
    double *a = (double *) malloc(N * sizeof(double));
    double *b = (double *) malloc(N * sizeof(double));

    aZero = c[0];
    a[N - 1] = c[N];

    for (int i = 0; i < N - 1; i++) {
        a[i] =  2.0 * creal(c[i + 1]);
        b[i] = -2.0 * cimag(c[i + 1]);
    }

    ezfftb (&nTermos, x, &aZero, a, b, wSave, iFac);

    for (int i = 0; i < N; i++) {
        f[i] = x[i];
        f[i + N] = x[i + N];
    }

    free(a);
    free(b);
    free(iFac);
    free(wSave);
    free(x);
}
