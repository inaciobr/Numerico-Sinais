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
 *
 *
 */
soundData readSoX(char file[]) {
    int lines = numberOfLines(file) - 2;
    soundData sox;

    if (!lines) {
        sox.sampleRate = 0;
        sox.numSamples = 0;
        sox.channels = 0;
        sox.ch1 = NULL;
        sox.ch2 = NULL;
        sox.duration = 0.0;

        return sox;
    }

    FILE *fp = fopen(file, "r");

    fscanf(fp, "; Sample Rate %d\n", &sox.sampleRate);
    fscanf(fp, "; Channels %d\n", &sox.channels);

    sox.ch1 = malloc((lines) * sizeof(double));
    sox.ch2 = sox.channels == 2 ? malloc((lines) * sizeof(double)) : NULL;
    sox.duration = (double)(lines - 1) / sox.sampleRate;
    sox.numSamples = lines;

    for (int i = 0; i < lines; i++) {
        fscanf(fp, "%*lf %lf", &sox.ch1[i]);

        if (sox.channels == 2)
            fscanf(fp, " %lf", &sox.ch2[i]);
    }

    fclose(fp);

    return sox;
}

/**
 *
 *
 */
void writeSoX(char file[], soundData sox) {
    FILE *fp = fopen(file, "w");

    fprintf(fp, "; Sample Rate %d\n", sox.sampleRate);
    fprintf(fp, "; Channels %d\n", sox.channels);

    double tempo = 0.0;
    for (int i = 0; i < sox.numSamples; i++) {
        fprintf(fp, " %15.8g  %15.11g ", tempo, sox.ch1[i]);

        if (sox.channels == 2)
            fprintf(fp, "%15.11g ", sox.ch2[i]);

        fprintf(fp, "%\n");

        tempo += 1.0 / sox.sampleRate;
    }

    fclose(fp);
}

/**
 *
 *
 */
void freeSoX(soundData *sox) {
    if (sox->ch1 != NULL)
        free(sox->ch1);

    if (sox->ch2 != NULL)
        free(sox->ch2);

    sox->sampleRate = 0;
    sox->numSamples = 0;
    sox->channels = 0;
    sox->ch1 = NULL;
    sox->ch2 = NULL;
    sox->duration = 0.0;
}

/**
 *
 *
 */
int numberOfLines(char file[]) {
    int lines = 0;
    char ch;

    FILE *fp = fopen(file, "r");

    if (fp == NULL)
        return 0;

    while ((ch = getc(fp)) != EOF)
        if (ch == '\n')
            lines++;

    fclose(fp);

    return lines;
}
