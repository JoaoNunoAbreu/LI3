#include "Produto.h"
#include <stdlib.h>
#include <string.h>

struct prod{
    char* linha;
};

char getIndex(Produto p, int index){
    return p->linha[index];
}
char* getCodProd(Produto p){
    return p->linha;
}
Produto criaProd(char* codProd){
    Produto p = malloc(sizeof(struct prod));
    p->linha = strdup(codProd);
    return p;
}