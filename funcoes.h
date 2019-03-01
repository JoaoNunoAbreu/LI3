#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct venda{
    char *produto;
    float preco;
    int quant;
    char promo;
    char *cliente;
    int mes;
    int filial;
}Vendas;

#define MAXBUFPRODCLIENT 7
#define MAXBUFVENDAS 32
#define MAXPRODS 200000
#define MAXCLIENT 20000
#define MAXVENDAS 1000000

// API

int elem(char** lista, char* key);
void linhaToArray(char* linha,char* tokensArray[7]);
void addVenda(Vendas* v, char* tokensArray[7], int index);
int validaClienteProduto(char* linha);
int validaVendas(char* tokensArray[7], char** listaProdutos, char** listaClientes);
int guardaProdutosClientes(FILE *fp, char** lista);
int guardaVendas(FILE *fp, char** listaVendas, char** listaProdutos, char** listaClientes, Vendas* vTodas, Vendas* vBoas, FILE* vValidasFicheiro);