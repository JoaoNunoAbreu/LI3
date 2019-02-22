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