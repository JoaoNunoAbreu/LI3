#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funcoes.h"

char* listaProdutos[MAXPRODS];
char* listaClientes[MAXCLIENT];
char* listaVendas[MAXVENDAS];


int main(int argc, char** argv) {

    // ---------------------------------- Abertura dos ficheiros ----------------------------------

    FILE *produtoFicheiro = fopen("Produtos.txt","r");
    if(produtoFicheiro == NULL) {printf("Produtos.txt não foi possível ser carregado."); exit (1);}
    FILE *clientesFicheiro = fopen("Clientes.txt","r");
    if(clientesFicheiro == NULL) {printf("Clientes.txt não foi possível ser carregado."); exit (1);}
    FILE *vendasFicheiro = fopen("Vendas_1M.txt","r");
    if(vendasFicheiro == NULL) {printf("Vendas.txt não foi possível ser carregado."); exit (1);}

    // ------------------------------------ Guarda nas listas -------------------------------------

    int pLidos = guardaProdutosClientes(produtoFicheiro,listaProdutos);
    printf("Foram lidas %d linhas do ficheiro produtos.txt\n",pLidos);

    int cLidos = guardaProdutosClientes(clientesFicheiro,listaClientes);
    printf("Foram lidas %d linhas do ficheiro clientes.txt\n",cLidos);

    Vendas* vendasTodas = malloc(MAXVENDAS * sizeof *vendasTodas);
    int vLidas = guardaVendasTodas(vendasFicheiro,listaVendas,vendasTodas);
    printf("Foram lidas %d linhas do ficheiro vendas.txt\n",vLidas);

    // --------- Vendas válidas ---------

    FILE *vValidasFicheiro = fopen("Vendas_1MValidas.txt","w");
    Vendas* vendasBoas = malloc(MAXVENDAS * sizeof *vendasBoas);
    int vLidasBoas = guardaVendasBoas(listaVendas,listaProdutos,listaClientes,vendasBoas,vValidasFicheiro);
    printf("Foram lidas %d linhas boas do ficheiro vendas.txt\n",vLidasBoas);
    //for(int i = 0; i < 10; i++) printf("%s %f %d %c %s %d %d\n", vendasBoas[i].produto,vendasBoas[i].preco,vendasBoas[i].quant,vendasBoas[i].promo,vendasBoas[i].cliente,vendasBoas[i].mes,vendasBoas[i].filial);

    // ----------------------------------- Close dos ficheiros ------------------------------------

    fclose(produtoFicheiro);
    fclose(clientesFicheiro);
    fclose(vendasFicheiro);

    return 0;
}