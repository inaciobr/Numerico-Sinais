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


    double complex F[4] = {5, -1, 3, 1};

    double complex s[4];
    //fftDireta(F, s, 4);
    fft2(s, F, 4, 1);
    for (int i = 0; i < 4; i++)
        printf("%f, %f\n", creal(s[i]), cimag(s[i]));

    printf("\n\n");

    double complex f[4];
    //fftInversa(f, s, 4);
    fft2(f, s, 4, 0);
    for (int i = 0; i < 4; i++)
        printf("%f, %f\n", creal(f[i]), cimag(f[i]));
/*


    soundData sox = readSoX(file);
    soundFrequency freq = SoX2Frequency(sox);
    soundData sox2 = frequency2SoX(freq);
    writeSoX("volta.dat", sox2);
*/

    return 0;
}
