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
#include <string.h>
#include <math.h>
#include <time.h>

#include "soundData.h"
#include "soundFrequency.h"
#include "fft.h"
#include "filtro.h"
#include "fftpack4.h"

void testesFFT(void (*fftd)(complex *, complex *, int), void (*ffti)(complex *, complex *, int));

int main() {
    char file[256];
    printf("EP 2 - ENGENHARIA ELETRICA\n"
           "Analise harmonica e Sinais Sonoros\n\n");


    printf("Digite o nome do arquivo que deseja ler.\n"
           "Por exemplo: \"dados_sons/dog.dat\".\nVoce pode digitar \"teste\" para visualizar os testes iniciais.\n"
           "Arquivo: ");
    scanf("%256[^\n]", file);


    FILE *fp = fopen(file, "r");
    fclose(fp);

    if (strcmp(file, "teste") && fp == NULL) {
        printf("%s nao foi encontrado.\n", file);
        return 0;
    }

    int menuFFT;
    void (*fftd)(complex *, complex *, int), (*ffti)(complex *, complex *, int);
    printf("\nSelecione a transformada que deseja utilizar: \n"
           "1 - Transformada lenta.\n"
           "2 - Transformada recursiva.\n"
           "3 - FFTPACK4.\n");

    scanf("%d", &menuFFT);

    switch (menuFFT) {
    case 1:
        fftd = &fftDireta;
        ffti = &fftInversa;
        break;

    case 2:
        fftd = &fftRecursivaDireta;
        ffti = &fftRecursivaInversa;
        break;

    case 3:
        fftd = &fftpack4Direta;
        ffti = &fftpack4Inversa;
        break;

    default:
        printf("Opcao invalida.\n");
        return 0;
    }

    if (!strcmp(file, "teste")) {
        testesFFT(fftd, ffti);

        return 0;
    }

    int menuFiltro, K1, K2;
    printf("\nSelecione um filtro para aplicar: \n"
           "0 - Sem filtros.\n"
           "1 - Filtro passa-baixa.\n"
           "2 - Filtro passa-alta.\n"
           "3 - Filtro passa-banda.\n"
           "4 - Filtro corta-banda.\n");
    scanf("%d", &menuFiltro);

    switch (menuFiltro) {
    case 0:
        break;

    case 1:
    case 2:
        printf("Digite o valor do indice K do filtro.");
        scanf("%d", &K1);
        break;

    case 3:
    case 4:
        printf("Digite o valor do menor indice K1.");
        scanf("%d", &K1);
        printf("Digite o valor do maior indice K2.");
        scanf("%d", &K2);
        break;

    default:
        printf("Opção de filtro inválida. O sinal será analisado sem a aplicação de filtros.");
        menuFiltro = 0;
    }


    int menuCompressao;
    double ampMin;
    printf("\nEscolha o tipo de compressao desejada: \n"
           "0 - Sem compressao.\n"
           "1 - Compressao cortando baixas amplitudes.\n");
    scanf("%d", &menuCompressao);

    if (menuCompressao == 1) {
        printf("\nDigite o valor \"e\" de corte da amplitude: ");
        scanf("%lf", &ampMin);
    }

    clock_t startTime = clock();

    soundData sox = readSoX(file, 1);
    soundFrequency freq = SoX2Frequency(sox, fftd);

    switch (menuFiltro) {
    case 1:
        filtroPassaBaixa(freq.channel1, freq.sizeChannel, K1);
        filtroPassaBaixa(freq.channel2, freq.sizeChannel, K1);
        break;

    case 2:
        filtroPassaAlta(freq.channel1, freq.sizeChannel, K1);
        filtroPassaAlta(freq.channel2, freq.sizeChannel, K1);
        break;

    case 3:
        filtroPassaFaixa(freq.channel1, freq.sizeChannel, K1, K2);
        filtroPassaFaixa(freq.channel2, freq.sizeChannel, K1, K2);
        break;

    case 4:
        filtroRejeitaFaixa(freq.channel1, freq.sizeChannel, K1, K2);
        filtroRejeitaFaixa(freq.channel2, freq.sizeChannel, K1, K2);
        break;
    }

    if (menuCompressao == 1) {
        double comp;

        comp = compressaoRemoveAmplitude(freq.channel1, freq.sizeChannel, ampMin);

        printf("\nCompressao de %.3f%% no canal 1.\n", 100. * comp);

        if (freq.channel2 != NULL) {
            comp = compressaoRemoveAmplitude(freq.channel1, freq.sizeChannel, ampMin);
            printf("Compressao de %.3f%% no canal 2.\n", 100. * comp);
        }
    }

    soundData sox2 = frequency2SoX(freq, ffti);

    printf("\nTempo para executar a funcao fft: %.3f\n", (double)(clock() - startTime) / CLOCKS_PER_SEC);

    writeFrequency("frequencias.dat", freq);
    writeSoX("novoAudio.dat", sox2);


    return 0;
}

/**
 *
 */
void testesFFT(void (*fftd)(complex *, complex *, int), void (*ffti)(complex *, complex *, int)) {
    int menuTestes;
    printf("\nEscolha qual teste deseja visualizar: \n"
           "1 - Teste 1.\n"
           "2 - Teste 2.\n"
           "3 - Teste 3.\n");
    scanf("%d", &menuTestes);

    if (menuTestes < 1 || menuTestes > 3) {
        printf("Teste inválido.");
        return 0;
    }

    int N;
    clock_t startTime, endTime;

    printf("\n========================== Teste %d ==========================\n", menuTestes);
    double complex *F, *c, *f;

    switch (menuTestes) {
    case 1:
        printf("Transformada de uma funcao com os seguintes valores em 0, pi/2, pi e 3*pi/2: (5, -1, 3, 1)\n");

        double complex F1[4] = {5, -1, 3, 1};
        double complex c1[4] = {}, f1[4] = {};

        N = 4;
        F = F1;
        c = c1;
        f = f1;

        break;


    case 2:
        printf("Transformada de uma funcao com os seguintes valores:  F = (6, 2, 5, 2, 11, 2, 8, 8)\n");

        double complex F2[8] = {6, 2, 5, 2, 11, 2, 8, 8};
        double complex c2[8] = {}, f2[8] = {};

        N = 8;
        F = F2;
        c = c2;
        f = f2;

        break;

    case 3:
        printf("Transformada de uma funcao F(x) = 10sin(x) + 7cos(30x) + 11sin(352x) - 8cos(711x)\n");

        double complex F3[1024] = {}, c3[1024] = {}, f3[1024] = {};
        for (int j = 0; j < 1024; j++) {
            double x = j * PI / 512.;
            F3[j] = 10*sin(x) + 7*cos(30*x) + 11*sin(352*x) - 8*cos(711*x);
        }

        N = 1024;
        F = F3;
        c = c3;
        f = f3;
    }


    startTime = clock();
    fftd(c, F, N);
    ffti(f, c, N);
    endTime = clock();

    printf("c = (");
    for (int i = 0; i < N; i++)
        printf("% -.3f%+.3fi, ", creal(c[i]), cimag(c[i]));

    printf("\b\b).\n\nAplicando agora a transformada inversa:\n"
           "f = (");

    for (int i = 0; i < N; i++)
        printf("% -.3f%+.3fi, ", creal(f[i]), cimag(f[i]));

    printf("\b\b).\n");

    printf("\nTempo para executar a funcao fft: %.3f s\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);
}
