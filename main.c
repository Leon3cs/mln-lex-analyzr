#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include "mln-lex-analyzr.h"

#define CONST_FREAD_PARAM 1

char alpha[ALNUM_LENGTH][ALNUM_LENGTH] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
    'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
    's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};

char num[NUM_LENGTH][NUM_LENGTH] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};

char openclose[OPEN_CLOSE_LENGTH][OPEN_CLOSE_LENGTH] = {
    '(', ')', '{', '}', '"'
};

char rel[REL_LENGTH][REL_LENGTH] = {
    '=', '<', '>'
};

char math[MATH_LENGTH][MATH_LENGTH] = {
    '+', '-', '*', '/', '%'
};

char atrib[ATRIB_LENGTH][ATRIB_LENGTH] = {
    ":="
};

char misc[MISC_LENGTH][MISC_LENGTH] = {
    ',', ';', '[', ']', ':'
};

char command[COMMAND_LENGTH][COMMAND_LENGTH] = {
    "for", "step", "sqrt", "if", "else", "return", "print", 
    "read", "to", "num", "string"
};

int main(){
    int selector;

    pointer p = malloc(sizeof(state));
    p->curlyBraces = 0;
    p->parentesis = 0;
    p->quotes = 0;

    setlocale(LC_ALL, "");

    printf("Select file (default is [1]):\n\n");
    printf("[1] - ArquivoFonte1.mln\n");
    printf("[2] - ArquivoFonte2.mln\n\n");
    printf(">> ");
    scanf("%d", &selector);

    if(selector == 2){
        analyzeFile("ArquivoFonte2.mln", &alpha, &num, &openclose, &rel, &math, &atrib, &misc, &command, p);
    }
    else{
        analyzeFile("ArquivoFonte1.mln", &alpha, &num, &openclose, &rel, &math, &atrib, &misc, &command, p);
    }
    
    return 0;
}
