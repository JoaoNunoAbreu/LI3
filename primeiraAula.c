#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main () {

    //listas
    char listaProdutos[200000][5];
    //char *listaClientes[20000];
    //char *listaVendas[1000000];

    FILE *product = fopen("Produtos.txt","r");
    //FILE *client = fopen("Clientes.txt","r");
    //FILE *vendas = fopen("Vendas.txt","r");



    // Guarda Produtos
    for (int i = 0;fgets(listaProdutos[i],sizeof listaProdutos,product);i++){
        printf("%s", listaProdutos[i]);
    }
    printf("\n");

    fclose(product);
    //fclose(client);
    //fclose(vendas);

    return 0;

}