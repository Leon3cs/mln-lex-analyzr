#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "constants.h"
#include "resultLogger.h"
#include "structs.h"

void isAlpha(char *character, char *alpha, char *num, char *openclose, char *rel, char *math, char *atrib, char *misc, int *line, int *row, FILE *result){
    int isValid = 0;
    
    if(checkOpenClose(character, openclose) != 1 &&
        checkRel(character, rel) != 1 &&
        checkMath(character, math) != 1 &&
        checkAtrib(character, atrib) != 1 &&
        checkMisc(character, misc) != 1 &&
        *character != ' ' &&
        *character != '\n' &&
        *character != '\r'
    ){
        if(checkNum(character, num) == 1){
            isValid = 1;
            return;
        }
        for(int i = 0; i < ALNUM_LENGTH; i++){
            char check = *alpha;
            
            if(*character == check){
                isValid = 1;
                break;
            }

            alpha++;
        }
    }else{
        isValid = 1;
    }

    if(isValid == 0){
        throwAlnumError(character, line, row, result);
    }
    
}

void isNum(char *character, char *word, char *num, int *line, int *row, FILE *result){
    if(checkNum(character, num) == 1){
        createNumberToken(character, word, line, row, result);
    }
}

void isCommandId(char *character, char *word, char *alpha, char *num, char *openclose, char *rel, char *math, char *atrib, char *misc, char *command, int *line, int *row, pointer state, FILE *result){
    int isValid = 0;
    
    for(int i = 0; i < COMMAND_LENGTH; i++){
        isValid = strcmp(word, command);
        if(isValid == 0){
            createKeywordToken(word, line, row, result);
            break;
        }
        command+=11;
    }

    if(isValid != 0){
        int idLength = 0;
        for(int i = 0; i < strlen(word); i++){
            for (int j = 0; j < ALNUM_LENGTH; j++)
            {
                char alnumCheck = *(alpha+j);
                char wordCheck = *(word+i);
                
                if(alnumCheck == wordCheck){
                    idLength++;
                    break;
                }
            }
        }

        if(strlen(word) > 0 && (idLength == strlen(word))){
            createIdToken(word, line, row, result);
        }else if(strlen(word) > 0){
            char number = *word;
            if(checkNum(&number, num) != 1){
                char check = *word;
                if(checkMath(&check, math) == 1){
                    return;
                }
                throwInvalidTokenError(word, line, row, result);
            }else{
                return;
            }
        }
    }
}

void isRel(char *character, char *rel, int *line, int *row, FILE *result){
    int isValid = 0;
    
    for(int i = 0; i < REL_LENGTH; i++){
        char relCheck = *rel;
        if(relCheck = *character){
            isValid = 1;
            break;
        }
        rel++;
    }

    if(isValid!=0){
        createRelToken(character, line, row, result);
    }
}

int checkRel(char *character, char *rel){
    int isValid = 0;
    
    for(int i = 0; i < REL_LENGTH; i++){
        char relCheck = *(rel+i);
        if(relCheck == *character){
            isValid = 1;
            break;
        }
    }

    if(isValid!=0){
        return 1;
    }else{
        return 0;
    }
}

int checkNum(char *character, char *num){
    int isValid = 0;
    
    for(int i = 0; i < MISC_LENGTH; i++){
        char numCheck = *(num+i);
        if(numCheck == *character){
            isValid = 1;
            break;
        }
    }

    if(isValid!=0){
        return 1;
    }else{
        return 0;
    }
}

int checkOpenClose(char *character, char *openclose){
    int isValid = 0;
    
    for(int i = 0; i < MISC_LENGTH; i++){
        char opencloseCheck = *(openclose+i);
        if(opencloseCheck == *character){
            isValid = 1;
            break;
        }
    }

    if(isValid!=0){
        return 1;
    }else{
        return 0;
    }
}

int checkMath(char *character, char *math){
    int isValid = 0;
    
    for(int i = 0; i < MISC_LENGTH; i++){
        char mathCheck = *(math+i);
        if(mathCheck == *character){
            isValid = 1;
            break;
        }
    }

    if(isValid!=0){
        return 1;
    }else{
        return 0;
    }
}

int checkAtrib(char *character, char *atrib){
    int isValid = 0;
    
    for(int i = 0; i < MISC_LENGTH; i++){
        char atribCheck = *(atrib+i);
        if(atribCheck == *character){
            isValid = 1;
            break;
        }
    }

    if(isValid!=0){
        return 1;
    }else{
        return 0;
    }
}

int checkMisc(char *character, char *misc){
    int isValid = 0;
    
    for(int i = 0; i < MISC_LENGTH; i++){
        char miscCheck = *(misc+i);
        if(miscCheck == *character){
            isValid = 1;
            break;
        }
    }

    if(isValid!=0){
        return 1;
    }else{
        return 0;
    }
}

void openCloseOperation(char *character, char *word, char *openclose, int *line, int *row, pointer state, FILE *result){
    switch(*character){
        case '(':
            state->parentesis++;
            break;
        case ')':
            state->parentesis--;
            break;
        case '{':
            state->curlyBraces++;
            break;
        case '}':
            state->curlyBraces--;
            break;
        case '"':
            state->quotes++;
            break;
        default:
            state = state;
    }

    logOpenCloseOperation(character, word, line, row, result);
}

void mathOperation(char *character, char *word, int *line, int *row, FILE *result){
    logMathOperation(character, word, line, row, result);
}
