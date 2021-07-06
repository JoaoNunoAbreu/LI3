#include "Cliente.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct client{
    char* linha;
};

char getChar0C(Cliente c){
    return c->linha[0];
}
char* getCodCliente(Cliente c){
    return strdup(c->linha);
}
Cliente criaCliente(char* codClient){
    Cliente c = malloc(sizeof(struct client));
    c->linha = strdup(codClient);
    return c;
}

int validaCliente(Cliente c){

    int r = 1;
    char* linha = getCodCliente(c);
    if(linha == NULL || strlen(linha) != 5) return 0;
    
    if(!isupper(linha[0])) r = 0;
    else {
        int num = atoi(linha+1);
        if(num < 1000 || num > 5000) r = 0;
    }

    return r;
}