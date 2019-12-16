#include <stdio.h>
#include <stdlib.h>

typedef struct state {
    int parentesis;
    int curlyBraces;
    int quotes;
} state;

typedef state *pointer;