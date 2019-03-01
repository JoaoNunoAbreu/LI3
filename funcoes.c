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

void linhaToArray(char* linha,char* tokensArray[7]){

    char* line = strdup(linha);
    char* token = strtok(line," ");
    int i = 0;
    while(token != NULL) {
        tokensArray[i] = token;    
        token = strtok(NULL," ");
        i++;
    }
}

void addVenda(Vendas* v, char* tokensArray[7], int index){

    v[index].produto = strdup(tokensArray[0]);
    v[index].preco = atof(tokensArray[1]);
    v[index].quant = atoi(tokensArray[2]);
    v[index].promo = *tokensArray[3];
    v[index].cliente = strdup(tokensArray[4]);
    v[index].mes = atoi(tokensArray[5]);
    v[index].filial = atoi(tokensArray[6]);
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
int validaVendas(char* tokensArray[7], char** listaProdutos, char** listaClientes){

    int r = 1;

    if(atof(tokensArray[1]) < 0 || atof(tokensArray[1]) > 999.99) r = 0;
    if(r == 1 && (atoi(tokensArray[2]) < 0 || atoi(tokensArray[2]) > 200)) r = 0;
    if(r == 1 && (*tokensArray[3] != 'N'   && *tokensArray[3] != 'P')) r = 0;
    if(r == 1 && (atoi(tokensArray[5]) < 0 || atoi(tokensArray[5]) > 12)) r = 0;
    if(r == 1 && (atoi(tokensArray[6]) < 0 || atoi(tokensArray[6]) > 3)) r = 0;
    //if(r == 1 && (!elem(listaClientes,tokensArray[4]))) r = 0;
    //if(r == 1 && (!elem(listaProdutos,tokensArray[0]))) r = 0;

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

// Guarda as vendas todas em array de strings e structs
int guardaVendas(FILE *fp, char** listaVendas, char** listaProdutos, char** listaClientes, Vendas* vTodas, Vendas* vBoas, FILE* vValidasFicheiro){

    char str[MAXBUFVENDAS];
    char* linha;
    int index = 0;
    char* tokensArray[7];
    int fail = 0; // conta quantas linhas inválidas foram lidas

    while(fgets(str,MAXBUFVENDAS,fp)){
        linha = strtok(str,"\n\r");
        linhaToArray(linha,tokensArray);
        if(validaVendas(tokensArray,listaProdutos,listaClientes)){
            listaVendas[index-fail] = strdup(linha); // Guarda em array de strings vendas válidas
            addVenda(vBoas,tokensArray,index-fail);
            fprintf(vValidasFicheiro,"%s\n",listaVendas[index-fail]);
        }
        else fail++;
        addVenda(vTodas,tokensArray,index); // Guarda em array de struct todas as vendas
        index++;
    }
    return index-fail;
}