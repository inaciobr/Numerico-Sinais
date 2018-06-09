/************************************************************
*                                                           *
*   Bruno Brandão Inácio - NUSP: 9838122                    *
*   Davi José Marques Vieira - NUSP 9838140                 *
*                                                           *
*************************************************************
* src/main.c                                                *
*************************************************************
* Funções principal do programa.                            *
* Realiza a interação com o usuário                         *
************************************************************/
#include <stdio.h>

#include "soundData.h"
#include "fft.h"

int main() {
    printf("EP 2 - ENGENHARIA ELETRICA\n"
           "Analise harmonica e Sinais Sonoros\n\n");

    char file[256] = "dados_sons/String-Guitar-C4.dat";
    printf("Digite o endereco do arquivo que deseja ler\n");
    /*scanf("%256[^\n]", file);*/


    soundData sox = readSoX(file);
    writeSoX("test.dat", sox);

    return 0;
}
