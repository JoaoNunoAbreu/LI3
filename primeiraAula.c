#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char listaClientes[20000][5];
    //char *listaProdutos[200000];
    //char *listaVendas[100000]; // não dá para criar com 1 milhão

    char strClientes[5];
    //char *strProdutos;
    //char *strVendas; // Usar depois tamanho da linha maior.

    FILE *clientes = fopen("Clientes.txt", "r");
    //FILE *produtos = fopen("Produtos.txt" , "r");
    //FILE *vendas = fopen("Vendas.txt" , "r");

    for(int i = 0;fgets(strClientes,5,clientes); i++){
        //printf("%s", strClientes);
        strcpy(listaClientes[i],strClientes);
        printf("%s", listaClientes[i]);
    }

    fclose(clientes);
    //fclose(produtos);
    //fclose(vendas);

    return 0;
}
