#include "Cliente.h"
#include <stdlib.h>
#include <string.h>

struct client{
    char* linha;
};

char getChar0C(Cliente p){
    return p->linha[0];
}
char* getCodCliente(Cliente p){
    return p->linha;
}
Cliente criaCliente(char* codClient){
    Cliente p = malloc(sizeof(struct client));
    p->linha = strdup(codClient);
    return p;
}