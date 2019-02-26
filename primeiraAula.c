#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct venda{
    char *produto;
    float preço;
    int quant;
    char promo_norm;
    char *cliente;
    int mes;
    int filial;
}*Venda;

#define MAXBUFPRODCLIENT 10
#define MAXPRODS 200000
#define MAXCLIENT 20000
#define MAXVENDAS 1000000
#define MAXBUFVENDAS 100

// ------------------------------------ Funções úteis globais -------------------------------------

// Dada uma linha da lista com "c" colunas, guarda na string "str" a linha "line".
char* getLine(char** lista, char *str, int line){
    str = strdup(lista[line]);
    return str;
}

// Procura uma linha na lista.
int elem(char** lista, char* key, int lines){

    int found = 0;

    for(int i = 0; i < lines; i++)
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

// ------------------------------------------------------------------------------------------------

int main(int argc, char** argv) {

    // ----------------- Listas -----------------
    char* listaProdutos[MAXPRODS];
    char* listaClientes[MAXCLIENT];
    char* listaVendas[MAXBUFVENDAS];

    // --------- Abertura dos ficheiros ---------
    FILE *produtoFicheiro = fopen("teste.txt","r"); // Está a usar o ficheiro teste
    if(produtoFicheiro == NULL) {printf("Produtos.txt não foi possível ser carregado."); exit (1);}
    FILE *clientesFicheiro = fopen("Clientes.txt","r");
    if(clientesFicheiro == NULL) {printf("Clientes.txt não foi possível ser carregado."); exit (1);}
    FILE *vendasFicheiro = fopen("Vendas.txt","r");
    if(vendasFicheiro == NULL) {printf("Vendas.txt não foi possível ser carregado."); exit (1);}

    // ----------- Guarda nas listas ------------

    int pLidas = guardaProdutosClientes(produtoFicheiro,listaProdutos);
    printf("Foram lidas %d linhas do ficheiro produtos.txt\n",pLidas);

    int cLidas = guardaProdutosClientes(clientesFicheiro,listaClientes);
    printf("Foram lidas %d linhas do ficheiro clientes.txt\n",cLidas);

    printf("%d", elem(listaProdutos,"DV1294",MAXPRODS));

    //int vLidas = guardaProdutosClientes(vendasFicheiro,listaVendas);
    //printf("Foram lidas %d linhas do ficheiro vendas.txt\n",vLidas);
    
    // --------------- Validação ----------------

    // Parte das repetições.

    /*int rep1 = 0;

    // Demora muito tempo.
    if(validaRep(pLidas,produtosColunas,listaProdutos,&rep1)) printf("Não há repetições nos produtos.\n");
    else printf("Há repetições nos produtos e a linha que se repete é %d.\n",rep1);*/

    /*int rep2 = 0;

    //if(validaRep(cLidas,clientesColunas,listaClientes,&rep2)) printf("Não há repetições nos clientes.\n");
    //else printf("Há repetições nos clientes e a linha que se repete é %d.\n",rep2);*/

    // ---------- Close dos ficheiros -----------

    fclose(produtoFicheiro);
    fclose(clientesFicheiro);
    fclose(vendasFicheiro);

    return 0;

}

/*
    NOTA:

    Validade de produtos (AB1234)
        - 2 letras maiúsculas
        - 4 dígitos entre 1000 e 9999
        - Sem repetidos (acho)

    Validade de clientes (A1234)
        - 1 letra maiúscula
        - 4 dígitos entre 1000 e 5000
        - Sem repetidos (acho)

    Validade de vendas (AB1234 123.12 123 N A1234 1 1)
        - Código de produto
        - Preço por unidade decimal entre 0.0 e 999.99
        - Número de unidades compradas entre 1 e 200
        - Compra normal ou promoção (N ou P)
        - Código do cliente
        - Mês da compra
        - Filial entre 1 e 3
        - Sem repetidos (acho)

    Objetivos:
        - Validar todas as componentes 
        - Armazenar apenas estas
        - Arranjar o melhor tamanho para o buffer do fgets()
        - Para validação das vendas fazer parsing de cada linha usando função strtok()
        - Guardar num ficheiro texto apenas as vendas válidas
        - Contar o total de dados válidos

*/