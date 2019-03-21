#include "Produto.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct prod{
    char* linha;
};

char getChar0P(Produto p){
    return p->linha[0];
}
char* getCodProd(Produto p){
    return strdup(p->linha);
}
Produto criaProd(char* codProd){
    Produto p = malloc(sizeof(struct prod));
    p->linha = strdup(codProd);
    return p;
}

int validaProduto(Produto p){

    int r = 1;
    char* linha = getCodProd(p);
    if(linha == NULL || strlen(linha) != 6) return 0;

    if(!isupper(linha[0]) || !isupper(linha[1])) r = 0;
    else{
        int num1 = atoi(linha+2);
        if(num1 < 1000 || num1 > 9999) r = 0;
    }
    return r;
}