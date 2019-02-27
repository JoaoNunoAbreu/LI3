#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funcoes.h"

// ------------------------------------ Funções úteis globais -------------------------------------

// Procura uma linha na lista.
int elem(char** lista, char* key){

    int found = 0;
    
    for(int i = 0; lista[i] != NULL && found == 0; i++){
        if(!strcmp(lista[i],key)) found = 1;
    }
    return found;
}

// --------------------------- Parte de validação (apenas de uma linha) ---------------------------

// Valida um cliente/produto.
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

// Valida uma venda.
int validaVendas(char* linha, char** listaProdutos, char** listaClientes, Vendas* v, int i){

    int r = 1;
    char* token = strtok(linha," ");
    char* tokensArray[7];

    int index = 0;
    while(token != NULL) {
        tokensArray[index] = token;    
        token = strtok(NULL," ");
        index++;
    }
    // -- Todos os tokens de uma linha guardados num array. --
    if(atof(tokensArray[1]) < 0 || atof(tokensArray[1]) > 999.99) r = 0;
    if(r == 1 && (atoi(tokensArray[2]) < 0 || atoi(tokensArray[2]) > 200)) r = 0;
    if(r == 1 && (*tokensArray[3] != 'N'   && *tokensArray[3] != 'P')) r = 0;
    if(r == 1 && (atoi(tokensArray[5]) < 0 || atoi(tokensArray[5]) > 12)) r = 0;
    if(r == 1 && (atoi(tokensArray[6]) < 0 || atoi(tokensArray[6]) > 3)) r = 0;
    //if(r == 1 && (!elem(listaClientes,tokensArray[4]))) r = 0;
    //if(r == 1 && (!elem(listaProdutos,tokensArray[0]))) r = 0;

    v[i].produto = strdup(tokensArray[0]);
    v[i].preco = atof(tokensArray[1]);
    v[i].quant = atoi(tokensArray[2]);
    v[i].promo = *tokensArray[3];
    v[i].cliente = strdup(tokensArray[4]);
    v[i].mes = atoi(tokensArray[5]);
    v[i].filial = atoi(tokensArray[6]);

    return r;
}

// --------------------------------- Parte de guardar nas listas ----------------------------------

// Guarda os produtos/clientes e retorna o número de linhas VÁLIDAS.
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

// Guarda as vendas VÁLIDAS (falta escrevê-las num ficheiro de texto)
int guardaVendas(FILE *fp, char** listaVendas, char** listaProdutos, char** listaClientes, Vendas v[MAXVENDAS]){

    char str[MAXBUFVENDAS];
    char* linha;
    int index = 0;

    while(fgets(str,MAXBUFVENDAS,fp)){
        linha = strtok(str,"\n\r");
        if(validaVendas(linha,listaProdutos,listaClientes,v,index)){
            listaVendas[index] = strdup(linha);
            index++;
        }
    }
    return index;
}

// ---------------------------------- Duvido que vá ser preciso -----------------------------------
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

// Dada uma linha da lista com "c" colunas, guarda na string "str" a linha "line".
char* getLine(char** lista, char *str, int line){
    str = strdup(lista[line]);
    return str;
}
*/