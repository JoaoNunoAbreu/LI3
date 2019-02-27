#include <stdio.h>
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
#define MAXBUFVENDAS 100
#define MAXPRODS 200000
#define MAXCLIENT 20000
#define MAXVENDAS 1000000

// API

int elem(char** lista, char* key);
int validaClienteProduto(char* linha);
int validaVendas(char* linha, char** listaProdutos, char** listaClientes, Vendas* v, int i);
int guardaProdutosClientes(FILE *fp, char** lista);
int guardaVendas(FILE *fp, char** listaVendas, char** listaProdutos, char** listaClientes, Vendas* v);
//char* getLine(char** lista, char *str, int line);
//int validaRep(int l, int c, char lista[l][c], int *rep);