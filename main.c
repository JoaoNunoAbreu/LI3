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
    FILE *vendasFicheiro = fopen("FicheirosTeste/testeVendas.txt","r");
    if(vendasFicheiro == NULL) {printf("Vendas.txt não foi possível ser carregado."); exit (1);}

    // ------------------------------------ Guarda nas listas -------------------------------------

    int pLidos = guardaProdutosClientes(produtoFicheiro,listaProdutos);
    printf("Foram lidas %d linhas válidas do ficheiro produtos.txt\n",pLidos);

    int cLidos = guardaProdutosClientes(clientesFicheiro,listaClientes);
    printf("Foram lidas %d linhas válidas do ficheiro clientes.txt\n",cLidos);

    // --------- Vendas válidas ---------

    FILE *vValidasFicheiro = fopen("Vendas_1MValidas.txt","w");
    Vendas* vTodas = malloc(MAXVENDAS * sizeof *vTodas);
    Vendas* vBoas = malloc(MAXVENDAS * sizeof *vBoas);

    int vLidas = guardaVendas(vendasFicheiro,listaVendas,listaProdutos,listaClientes,vTodas,vBoas,vValidasFicheiro);
    printf("Foram lidas %d linhas válidas do ficheiro vendas.txt\n",vLidas);

    // ----------------------------------- Close dos ficheiros ------------------------------------

    fclose(produtoFicheiro);
    fclose(clientesFicheiro);
    fclose(vendasFicheiro);

    return 0;
}