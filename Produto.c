#include "Produto.h"
#include <stdlib.h>
#include <string.h>

struct prod{
    char* linha;
};

char getChar0P(Produto p){
    return p->linha[0];
}
char* getCodProd(Produto p){
    return p->linha;
}
Produto criaProd(char* codProd){
    Produto p = malloc(sizeof(struct prod));
    p->linha = strdup(codProd);
    return p;
}