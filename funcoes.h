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
void linhaToArray(char* linha,char* tokensArray[7]);
void addVenda(Vendas* v, char* tokensArray[7], int index);
int validaClienteProduto(char* linha);
int validaVendas(char* tokensArray[7], char** listaProdutos, char** listaClientes);
int guardaProdutosClientes(FILE *fp, char** lista);
int guardaVendasTodas(FILE *fp, char** listaVendas, Vendas* v);
int guardaVendasBoas(char** listaVendas, char** listaProdutos, char** listaClientes, Vendas* v, FILE* vValidasFicheiro);
//char* getLine(char** lista, char *str, int line);
//int validaRep(int l, int c, char lista[l][c], int *rep);