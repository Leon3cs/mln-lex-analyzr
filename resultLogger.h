#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "constants.h"

FILE* openResultFile()
{
    FILE* result = fopen("results.txt", "w");
    if(result == NULL)
    {
        printf("\n[ERROR][000] not able to create result file");
        return NULL;
    }

    return result;
}

void closeResultFile(FILE *result)
{
    fclose(result);
}

void throwAlnumError(char *character, int *line, int *row, FILE *result){
    fprintf(result, "Invalid character: [%c] at %d:%d", *character, *line, *row);
    fputc('\n', result);
}

void createKeywordToken(char *word, int *line, int *row, FILE *result){
    fprintf(result, "<keyword:%s> at %d:%d", word, *line, *row);
    fputc('\n', result);
    strcpy(word, "");
}

void createIdToken(char *word, int *line, int *row, FILE *result){
    fprintf(result, "<id:%s> at %d:%d", word, *line, *row);
    fputc('\n', result);
    strcpy(word, "");
}

void throwInvalidTokenError(char *word, int *line, int *row, FILE *result){
    fprintf(result, "Invalid token: [%s] at %d:%d", word, *line, *row);
    fputc('\n', result);
    strcpy(word, "");
}

void createRelToken(char *character, int *line, int *row, FILE *result){
    fprintf(result, "<%c> at %d:%d", *character, *line, *row);
    fputc('\n', result);
}

void createNumberToken(char *character, char *word, int *line, int *row, FILE *result){
    fprintf(result, "<number:%c> at %d, %d", *character, *line, *row);
    fputc('\n', result);
    strcpy(word, "");
}

void logOpenCloseOperation(char *character, char *word, int *line, int *row, FILE *result){
    fprintf(result, "<%c> at %d:%d", *character, *line, *row);
    fputc('\n', result);
    strcpy(word, "");
}

void logMathOperation(char *character, char *word, int *line, int *row, FILE *result){
    fprintf(result, "<%c> at %d:%d", *character, *line, *row);
    fputc('\n', result);
}
