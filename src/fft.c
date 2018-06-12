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
 *
 * 2N = nTermos
 *
 */
void fftDireta(double complex *F, double complex *ck, int nTermos) {
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

        ck[k] = (even + odd) / nTermos;
        ck[k + N] = (even - odd) / nTermos;
    }
}

void fftInversa(double complex *F, double complex *ck, int nTermos) {
    double complex odd, even, fase;
    int N = nTermos / 2;

    for (int j = 0; j < N; j++) {
        odd = even = 0.0;

        for (int k = 0; k < N; k++) {
            fase = cexp(1i * k * PI * j / (N/2));
            even += ck[2*k] * fase;
            odd += ck[2*k + 1] * fase;
        }

        odd *= cexp(1i * j * PI / N);

        F[j] = (even + odd);
        F[j + N] = (even - odd);
    }
}


/**
fftrec(double complex *c, double complex *f, int n, int dir){
    fimpar = malloc((int)(n/2) * sizeof(double complex*));
    fpar = malloc(((int)(n/2)) + 1)* sizeof(double complex*));

    if(n == 1){
        c[0] = f[0] + f[1];
        c[1] = f[0] - f[1];

    }else{
        for(int j = 0;j < n;j++){
            fpar[j] = f[2*j];
            fimpar[j] = f[2*j+1];
        }
    }
    fftrec(par,fpar,n/2,dir);
    fftrec(impar,fimpar,n/2,dir);

    for(int i = 0; i < n - 1; i++){
        if(dir){

        }
    }
}
***/


/*
fftrec(c,f,n,dir)
complexos f(0:2n-1),c(0:2n-1),even(0:n-1),odd(0:n-1),fe(0:n-1),fo(0:n-1)
logico dir
Se n=1 ent˜ao
c(0) = f(0)+f(1)
c(1) = f(0)-f(1)
sen˜ao
para j=0,n-1
fe(j)=f(2j)
fo(j)=f(2j+1)
fim do para
fftrec(even,fe,n/2,dir)
fftrec(odd ,fo,n/2,dir)
para j=0,n-1
se (dir) ent˜ao
eij = exp(- i * j * pi / n)
sen˜ao
eij = exp(i * j * pi / n)
fim do se
c(j) = even(j)+eij * odd(j)
c(j+n) = even(j)-eij * odd(j)
fim do para
fim do se
*/
