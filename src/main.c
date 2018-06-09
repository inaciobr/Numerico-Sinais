#include <stdio.h>

#include "soundData.h"

int main() {
    char file[256] = "dados_sons/String-Guitar-C4.dat";
    printf("EP 2 - ENGENHARIA ELETRICA\n"
           "Analise harmonica e Sinais Sonoros\n\n");

    printf("Digite o endereco do arquivo que deseja ler\n");
    /*scanf("%256[^\n]", file);*/

    soundData sox = readSoX(file);

    writeSoX("test.dat", sox);

    return 0;
}
