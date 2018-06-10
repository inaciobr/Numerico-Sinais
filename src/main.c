/************************************************************
*                                                           *
*   Bruno Brandão Inácio - NUSP: 9838122                    *
*   Davi José Marques Vieira - NUSP 9838140                 *
*                                                           *
*************************************************************
* src/main.c                                                *
*************************************************************
* Funções principal do programa.                            *
* Realiza a interação com o usuário.                        *
************************************************************/
#include <stdio.h>

#include "soundData.h"
#include "soundFrequency.h"
#include "fft.h"

int main() {
    printf("EP 2 - ENGENHARIA ELETRICA\n"
           "Analise harmonica e Sinais Sonoros\n\n");

    char file[256] = "dados_sons/hanks_apollo_problem.dat";
    printf("Digite o endereco do arquivo que deseja ler\n");
    /*scanf("%256[^\n]", file);*/

/*
    double complex F[4] = {5, -1, 3, 1};

    double complex *s = fftDireta(F, 4);
    for (int i = 0; i < 4; i++)
        printf("%f, %f\n", creal(s[i]), cimag(s[i]));

    printf("\n\n");

    double complex *f = fftInversa(s, 4);
    for (int i = 0; i < 4; i++)
        printf("%f, %f\n", creal(f[i]), cimag(f[i]));
*/


    soundData sox = readSoX(file);
    soundFrequency freq = SoX2Frequency(sox);

    FILE *fp = fopen ("test.txt", "w");
    for (int i = 0; i < sox.numSamples; i++)
        fprintf(fp, "%d, %f, %f\n", i, cabs(freq.cAmplitude[i]), carg(freq.cAmplitude[i]));

    fclose(fp);

    return 0;
}
