#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct venda{
    char *produto;
    float preco;
    int quant;
    char promo;
    char *cliente;
    int mes;
    int filial;
}Vendas;

#define MAXBUFPROD 7
#define MAXBUFCLIENT 6
#define MAXBUFVENDAS 32
#define MAXPRODS 200000
#define MAXCLIENT 20000
#define MAXVENDAS 1000000

// API

int elem(char** lista, char* key);
void linhaToArray(char* linha,char* tokensArray[7]);
int contaChar(char* iniciais, char x);
int contaFilial(Vendas* v, int filial);
float contaFaturacao(Vendas*v);
void addVenda(Vendas* v, char* tokensArray[7], int index);
int contaVendas(Vendas* v, char* cliente);
int validaCliente(char* linha);
int validaProduto(char* linha);
int validaVendas(char* tokensArray[7], char** listaProdutos, char** listaClientes);
int guardaClientes(FILE *fp, char** lista);
int guardaProdutos(FILE *fp, char** lista);
int guardaVendas(FILE *fp, char** listaVendas, char** listaProdutos, char** listaClientes, Vendas* vTodas, Vendas* vBoas, FILE* vValidasFicheiro);