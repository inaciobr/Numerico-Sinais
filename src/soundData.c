/************************************************************
*                                                           *
*   Bruno Brandão Inácio - NUSP: 9838122                    *
*   Davi José Marques Vieira - NUSP 9838140                 *
*                                                           *
*************************************************************
* src/soundData.c                                           *
*************************************************************
* Funções relacionadas a leitura e escrita de arquivos .dat *
* no padrão do software SoX - SOund eXchange                *
************************************************************/

#include "soundData.h"

/**
 * Inicializa a struct soundData com os valores lidos
 * de um arquivo .dat no formato do software SoX.
 */
soundData readSoX(char file[], int power2) {
    soundData sox;

    int lines = numberOfLines(file) - 2;

    if (!lines) {
		freeSoX(&sox);
        return sox;
    }

    FILE *fp = fopen(file, "r");

    fscanf(fp, "; Sample Rate %d\n", &sox.sampleRate);
    fscanf(fp, "; Channels %d\n", &sox.channels);

    sox.numSamples = lines;
    sox.sizeChannel = power2 ? nearestPower2(lines) : lines;

    sox.channel1 = malloc(sox.sizeChannel * sizeof(double));
    sox.channel2 = sox.channels == 2 ? malloc(sox.sizeChannel * sizeof(double)) : NULL;
    sox.duration = (double)(lines - 1) / sox.sampleRate;

    for (int i = 0; i < lines; i++) {
        fscanf(fp, "%*f %lf", &sox.channel1[i]);

        if (sox.channels == 2)
            fscanf(fp, " %lf", &sox.channel2[i]);
    }

    fclose(fp);

    if (power2) {
        completaPotencia2(sox.channel1, sox.numSamples, sox.sizeChannel);

        if (sox.channels == 2)
            completaPotencia2(sox.channel2, sox.numSamples, sox.sizeChannel);
    }

    return sox;
}

/**
 * Escreve um arquivo .dat em formato que pode ser lido pelo
 * software SoX com base nos dados armazenados na struct soundData.
 */
void writeSoX(char file[], soundData sox) {
    FILE *fp = fopen(file, "w");

    fprintf(fp, "; Sample Rate %d\n", sox.sampleRate);
    fprintf(fp, "; Channels %d\n", sox.channels);

    double tempo = 0.0;
    for (int i = 0; i < sox.numSamples; i++) {
        fprintf(fp, " %15.8g  %15.11g ", tempo, sox.channel1[i]);

        if (sox.channels == 2)
            fprintf(fp, "%15.11g ", sox.channel2[i]);

        fprintf(fp, "\n");

        tempo += 1.0 / sox.sampleRate;
    }

    fclose(fp);
}

/**
 * Libera o espaço alocado para construir uma
 * struct soundData.
 */
void freeSoX(soundData *sox) {
    if (sox->channel1 != NULL)
        free(sox->channel1);

    if (sox->channel2 != NULL)
        free(sox->channel2);

    sox->sampleRate = 0;
    sox->numSamples = 0;
    sox->channels = 0;
    sox->channel1 = NULL;
    sox->channel2 = NULL;
    sox->duration = 0.0;
    sox->sizeChannel = 0;
}

/**
 * Função para obter o número de linhas de um arquivo.
 */
int numberOfLines(char file[]) {
    FILE *fp = fopen(file, "r");
    if (fp == NULL)
        return 0;

    int lines = 0;
    char ch;

    while ((ch = getc(fp)) != EOF)
        if (ch == '\n')
            lines++;

    fclose(fp);

    return lines;
}

/**
 * Encontra a menor potência de dois superior a um número N.
 */
int nearestPower2(int N) {
	int nPower2 = 1 << (int) log2(N);

	if (N > 1. * nPower2)
        nPower2 <<= 1;

	return nPower2;
}

/**
 * Calcula a média dos valores de um sinal.
 */
double calculaMedia(double *f, int nTermos) {
	double soma = 0.0;

	for (int i = 0; i < nTermos; i++)
		soma += f[i];

	return soma / nTermos;
}

/**
 * Preenche os novos valores de um sinal transformado
 * para potência de 2 com a média deste sinal.
 */
void completaPotencia2(double *F, int tamanhoAntigo, int tamanhoNovo) {
	double complex avg = calculaMedia(F, tamanhoAntigo);

    for (int i = tamanhoAntigo; i < tamanhoNovo; i++)
		F[i] = avg;
}
