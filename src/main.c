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
#include "filtro.h"

int main() {
    printf("EP 2 - ENGENHARIA ELETRICA\n"
           "Analise harmonica e Sinais Sonoros\n\n");

    char file[256] = "dados_sons/hanks_apollo_problem.dat";
    printf("Digite o nome do arquivo que deseja ler. Ele deve estar dentro da pasta \"dados_sons\"\n");
    printf("Por exemplo: \"dog.dat\"\n");
    printf("Arquivo: ");
    //scanf("%256[^\n]", &file[strlen(file)]);

    if (!numberOfLines(file)) {
        printf("%s nao foi encontrado.\n", file);

        return 0;
    }

/*
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
*/


    soundData sox = readSoX(file);
    soundFrequency freq = SoX2FrequencyDireta(sox);



    //filtroPassaBaixa(freq.channel1, freq.size, freq.frequency, 2000.0);
    //filtroPassaBaixa(freq.channel2, freq.size, freq.frequency, 2000.0);

    //filtroPassaAlta(freq.channel1, freq.size, freq.frequency, 3000.0);
    //filtroPassaAlta(freq.channel2, freq.size, freq.frequency, 3000.0);

    //filtroPassaFaixa(freq.channel1, freq.size, freq.frequency, 780.0, 800.0);
    //filtroPassaFaixa(freq.channel2, freq.size, freq.frequency, 780.0, 800.0);

    //printf("%f", freq.frequency);

    soundData sox2 = frequency2SoXDireta(freq);
    writeSoX("volta.dat", sox2);


    return 0;
}
