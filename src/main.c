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
void fftpack4Direta(complex *c, complex *f, int nTermos);
void fftpack4Inversa(complex *c, complex *f, int nTermos);

int main() {
    char dir[256] = "dados_sons/";
    char file[256];
    printf("EP 2 - ENGENHARIA ELETRICA\n"
           "Analise harmonica e Sinais Sonoros\n\n");


    printf("Digite o nome do arquivo que deseja ler. Ele deve estar dentro da pasta \"dados_sons\".\n"
           "Por exemplo: \"dog.dat\". Voce pode digitar \"Teste\" para visualizar os testes iniciais.\n"
           "Arquivo: ");
    scanf("%256[^\n]", file);


    if (strcmp(file, "teste")) {
        strcat(dir, file);

        if (!numberOfLines(dir)) {
            printf("%s nao foi encontrado.\n", dir);
            return 0;
        }
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

    clock_t startTime = clock();

    //testesFFT(fftd, ffti);


    soundData sox = readSoX(dir, 1);
    soundFrequency freq = SoX2Frequency(sox, fftd);


    filtroPassaBaixa(freq.channel1, freq.sizeChannel, freq.frequency, 25000.0 * freq.frequency);
    filtroPassaBaixa(freq.channel2, freq.sizeChannel, freq.frequency, 25000.0 * freq.frequency);

    //filtroPassaAlta(freq.channel1, freq.size, freq.frequency, 4000.0 * freq.frequency);
    //filtroPassaAlta(freq.channel2, freq.size, freq.frequency, 4000.0 * freq.frequency);

    //filtroPassaFaixa(freq.channel1, freq.size, freq.frequency, 780.0, 800.0);
    //filtroPassaFaixa(freq.channel2, freq.size, freq.frequency, 780.0, 800.0);


    //printf("%f", freq.frequency);

    soundData sox2 = frequency2SoX(freq, ffti);

    printf("Tempo para executar a funcao fft: %.3f\n", (double)(clock() - startTime) / CLOCKS_PER_SEC);

    writeFrequency("freq.dat", freq);
    writeSoX("volta.dat", sox2);


    return 0;
}


void testesFFT(void (*fftd)(complex *, complex *, int), void (*ffti)(complex *, complex *, int)) {
    clock_t startTime, endTime;
    /** TESTE 1**/
    printf("\n========================== Teste 1 ==========================\n"
           "Transformada de uma funcao com os seguintes valores em 0, pi/2, pi e 3*pi/2: (5, -1, 3, 1)\n c = (");
    double complex F1[4] = {5, -1, 3, 1};
    double complex c1[4] = {}, f1[4] = {};

    startTime = clock();
    fftd(c1, F1, 4);
    ffti(f1, c1, 4);
    endTime = clock();

    for (int i = 0; i < 4; i++)
        printf("% -.1f%+.1fi, ", creal(c1[i]), cimag(c1[i]));

    printf("\b\b).\n\nAplicando agora a transformada inversa:\n f = (");

    for (int i = 0; i < 4; i++)
        printf("% -.1f%+.1fi, ", creal(f1[i]), cimag(f1[i]));

    printf("\b\b).\n");
    printf("Tempo para executar a funcao fft: %.3f s\n\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);



    /** TESTE 2**/
    printf("\n========================== Teste 2 ==========================\n"
           "Transformada de uma funcao com os seguintes valores:  F = (6, 2, 5, 2, 11, 2, 8, 8)\n c = (");
    double complex F2[8] = {6, 2, 5, 2, 11, 2, 8, 8};
    double complex c2[8] = {}, f2[8] = {};

    startTime = clock();
    fftd(c2, F2, 8);
    ffti(f2, c2, 8);
    endTime = clock();

    for (int i = 0; i < 8; i++)
        printf("% -.3f%+.3fi, ", creal(c2[i]), cimag(c2[i]));

    printf("\b\b).\n\nAplicando agora a transformada inversa:\n f = (");

    for (int i = 0; i < 8; i++)
        printf("% -.3f%+.3fi, ", creal(f2[i]), cimag(f2[i]));

    printf("\b\b).\n");
    printf("Tempo para executar a funcao fft: %.3f s\n\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);


    /** TESTE 3**/
    printf("========================== Teste 3 ==========================\n"
           "Transformada de uma funcao F(x) = 10sin(x) + 7cos(30x) + 11sin(352x) - 8cos(711x)\n c = (");
    double complex F3[1024] = {}, c3[1024] = {}, f3[1024] = {};

    for (int j = 0; j < 1024; j++) {
        double x = j * PI / 512.;
        F3[j] = 10*sin(x) + 7*cos(30*x) + 11*sin(352*x) - 8*cos(711*x);
    }

    startTime = clock();
    fftd(c3, F3, 1024);
    ffti(f3, c3, 1024);
    endTime = clock();

    for (int i = 0; i < 1024; i++)
        printf("% -.3f%+.3fi, ", creal(c3[i]), cimag(c3[i]));

    printf("\b\b).\n\nAplicando agora a transformada inversa:\n f = (");

    for (int i = 0; i < 1024; i++)
        printf("% -.3f%+.3fi, ", creal(f3[i]), cimag(f3[i]));

    printf("\b\b).\n");
    printf("Tempo para executar a funcao fft: %.3f s\n\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);

}
