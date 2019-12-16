#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "validator.h"

void analyzeFile(char *fileName, char *alpha, char *num, char *openclose, char *rel, char *math, char *atrib, char *misc, char *command, pointer state){
    FILE* file = fopen(fileName, "r");
    FILE* result = openResultFile();
    char character[1];
    char word[500];
    int string;
    word[0] = NULL;
    int i = 1, j = 1;

    if(file == NULL){
        printf("\n[ERROR][001] file not found or does not exits");
        return;
    }

    while(!feof(file)){
        fread(character, CONST_FREAD_PARAM, CONST_FREAD_PARAM, file);
        if(*character != '\n'){
            int wordCmp = strcmp(word, "");
            if(checkOpenClose(&character, openclose)){
                openCloseOperation(&character, word, openclose, &j, &i, state, result);
            }
            if(checkMath(&character, math)){
                mathOperation(&character, word, &j, &i, result);
            }
            if(checkRel(&character, rel)){
                mathOperation(&character, word, &j, &i, result);
            }
            if(checkNum(&character, num)){
                isNum(&character, word, num, &j, &i, result);
            }
            isAlpha(&character, alpha, num, openclose, rel, math, atrib, misc, &j, &i, result);
            if(checkRel(&character, rel) != 1 && checkMisc(&character, misc) != 1 && checkOpenClose(&character, openclose) != 1 && *character != '\r' && *character != ' '){
                strncat(word, character, 1);
            }else if(wordCmp!=0){
                isCommandId(&character, word, alpha, num, openclose, rel, math, atrib, misc, command, &j, &i, state, result);
            }else{
                continue;
            }
        }else{
            strcpy(word, "");
        }
        i++;
        if(character[0] == '\n'){
            j++;
            i = 1;
        }
    }

    fclose(file);
    closeResultFile(result);
}