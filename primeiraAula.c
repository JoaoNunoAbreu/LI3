#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char *listaProdutos[200000];
    char *listaClientes[20000];
    char *listaVendas[100000]; // não dá para criar com 1 milhão

    char *strClientes;
    char *strProdutos;
    char *strVendas; // Usar depois tamanho da linha maior.

    FILE *clientes = fopen("Clientes.txt", "r");
    FILE *produtos = fopen("Produtos.txt" , "r");
    FILE *vendas = fopen("Vendas.txt" , "r");

    for(int i = 0; clientes != NULL && i < 20000; i++){
            fgets(strClientes,5,clientes);
            
            strcpy(listaClientes[i],strClientes); // Segmentation fault aqui
        
        printf("%s\n",listaClientes[i]);
    }

    fclose(clientes);
    fclose(produtos);
    fclose(vendas);

    return 0;
}
