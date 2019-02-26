#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funcoes.h"

int main(int argc, char** argv) {

    // ----------------- Listas -----------------
    char* listaProdutos[MAXPRODS];
    char* listaClientes[MAXCLIENT];
    char* listaVendas[MAXBUFVENDAS];

    // --------- Abertura dos ficheiros ---------
    FILE *produtoFicheiro = fopen("Produtos.txt","r"); // Está a usar o ficheiro teste
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

    //printf("%d", elem(listaProdutos,"DV1294",MAXPRODS));

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