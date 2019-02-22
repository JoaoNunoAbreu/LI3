#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// ------------ Estas 2 funções são muito semelhantes, provavelmente dá para fazer tudo numa ------

// Guarda os produtos e retorna a quantidade de linhas lidas.
int guardaProdutos(char listaProdutos[200000][6],FILE *produto){

    int i;

    for (i = 0;fgets(listaProdutos[i],8,produto);i++) // 8 é o valor mínimo que me dá bem
        printf("%s", listaProdutos[i]); // Não é necessário dar print, é só para ver se está a fazer corretamente
    printf("\n"); // Efeitos estética no terminal
    return i;
}

// Guarda os clientes e retorna a quantidade de linhas lidas.
int guardaClientes(char listaClientes[20000][5], FILE *clientes){

    int i;

    for (i = 0;fgets(listaClientes[i],7,clientes);i++) // 7 é o valor mínimo que me dá bem
        printf("%s", listaClientes[i]); // Não é necessário dar print, é só para ver se está a fazer corretamente
    printf("\n"); // Efeitos estética no terminal
    return i;
}

// ------------------------------------------------------------------------------------------------

int main () {

    // ----------------- Listas -----------------
    char listaProdutos[200000][6];
    char listaClientes[20000][5];
    //char listaVendas[1000000][100]; // dá seg fault porque array é demasiado grande

    // --------- Abertura dos ficheiros ---------
    FILE *produto = fopen("Produtos.txt","r");
    FILE *clientes = fopen("Clientes.txt","r");
    FILE *vendas = fopen("Vendas.txt","r");

    // ----------- Guarda nas listas ------------

    //int r1 = guardaProdutos(listaProdutos,produto);
    //printf("Foram lidas %d linhas do ficheiro produtos.txt\n",r1);

    int r2 = guardaClientes(listaClientes,clientes);
    printf("Foram lidas %d linhas do ficheiro clientes\n",r2);
    
    // ---------- Close dos ficheiros -----------

    fclose(product);
    fclose(client);
    fclose(vendas);

    return 0;

}