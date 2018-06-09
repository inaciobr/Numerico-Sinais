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
 *
 */
double complex dimpar(double complex* F, int ntermos, int k){
    int n = (int)(ntermos/2);
    double complex fimpar = 0.0;


    for(int j = 0;j < n;j++){
        fimpar += F[2*j+1]*cexp(-1i*k*pi*j*2/n);
    }

    return fimpar;
}

/**
 *
 *
 */
double complex dpar(double complex* F, int ntermos, int k){
    int n = (int)(ntermos/2);
    double complex fpar = 0.0;

    for(int j = 0;j < n;j++){
            fpar += F[2*j]*cexp(-1i*k*pi*j*2/n);
    }

    return fpar;
}

/**
 *
 *MANO, TA BICHADO O NUMERO DE ELEMENTOS SEPA, EU NAO SEI --- parte do k + N, como fica os de 0 a k??
 */
double complex* fftdireta(double complex* F, int ntermos){// termos = 2N

   double complex* ck = malloc(ntermos * sizeof(double complex*));

    for(int k = 0;k < ntermos/2 ;k++){
        ck[k] = dpar(&F,ntermos,k) - cexp(-1i*k*pi*2/ntermos)*dimpar(&F,ntermos,k);
    }

    return ck;
}

/**
 *
 *
 */
double complex* fftinversa(double complex* ck, int ntermos){
    double complex* F = malloc(ntermos * sizeof(double complex*));

    for(int j = 0; j < ntermos; j++){
        if(j < ntermos/2){
            F[j] = ipar(&ck,ntermos,j) + cexp(1i*pi*j*2/ntermos)*iimpar(&ck,ntermos,j);
        }else{
            F[j] = ipar(&ck,ntermos,j) - cexp(1i*pi*j*2/ntermos)*iimpar(&ck,ntermos,j);
        }
    }

    return F;
}



/**
fftrec(double complex* c, double complex* f,int n,int dir){
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
