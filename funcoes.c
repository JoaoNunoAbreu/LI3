#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funcoes.h"

// ------------------------------------ Funções úteis globais -------------------------------------

// Dada uma linha da lista com "c" colunas, guarda na string "str" a linha "line".
char* getLine(char** lista, char *str, int line){
    str = strdup(lista[line]);
    return str;
}

// Procura uma linha na lista.
int elem(char** lista, char* key){

    int found = 0;
    
    for(int i = 0; lista[i] != NULL; i++)
        if(!strcmp(lista[i],key)) found = 1;

    return found;
}

// -------------------------------------- Parte de validação --------------------------------------

// Testa a estrutura dos clientes e dos produtos.
int validaClienteProduto(char* linha){
    int r = 1;
    int f; // 0 se produto, 1 se cliente
    if(linha == NULL) return 0; // No caso da linha lida ser vazia.
    if(strlen(linha) == 5) f = 1;
    else if(strlen(linha) == 6) f = 0;
    else return 0;
    
    if(f){
        if(!isupper(linha[0])) r = 0;
        else {
            int num = atoi(linha+1);
            if(num < 1000 || num > 5000) r = 0;
        }
    }
    else {
        if(!isupper(linha[0]) || !isupper(linha[1])) r = 0;
        else{
            int num1 = atoi(linha+2);
            if(num1 < 1000 || num1 > 9999) r = 0;
        }
    }
    return r;
}

// Valida a estrutura de uma venda.
int validaVendas(char* linha, char** produto){

    int r = 1;
    char* token = strtok(linha," ");
    char* tokensArray[7];

    int index = 0;
    while(token != NULL) {
        tokensArray[index] = token;    
        printf("%s\n", tokensArray[index]);
        token = strtok(NULL," ");
    }
    // A este ponto temos todos os tokens de uma linha guardados num array.
    //if(elem(produto,tokensArray[0],))
    return r;
}

/*
// Testa se há repetições numa lista.
int validaRep(int l, int c, char lista[l][c], int *rep){

    int r = 1;
    char str[c+1];

    for(int i = 0; i < l; i++){
        getLine(i,c,lista,str);
        if(elem(i,c,lista,str)){ 
            r = 0;
            *rep = i+1;
        }
    }
    return r;
}
*/

// --------------------------------- Parte de guardar nas listas ----------------------------------

// Guarda os produtos/clientes e retorna a quantidade de linhas lidas.
int guardaProdutosClientes(FILE *fp, char** lista){

    char str[MAXBUFPRODCLIENT];
    char* linha;

    int index = 0;
    while(fgets(str,MAXBUFPRODCLIENT,fp)){
        linha = strtok(str,"\n\r");
        if(validaClienteProduto(linha)){
            lista[index] = strdup(linha);
            index++;
        }
    }
    return index;
}

int guardaVendas(FILE *fp, char** lista){

    char str[MAXBUFVENDAS];
    char* linha;

    int index = 0;
    while(fgets(str,MAXBUFVENDAS,fp)){
        linha = strtok(str,"\n\r");
        lista[index] = strdup(linha);
        index++;
    }
    return index;
}