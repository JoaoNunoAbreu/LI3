#define _GNU_SOURCE
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

char* listaProdutos[MAXPRODS];
char* listaClientes[MAXCLIENT];
char* listaVendas[MAXVENDAS];

char* envolvidosP[MAXPRODS];
char* envolvidosC[MAXCLIENT];

/* ------------------------------------ Funções úteis globais -----------------------------------*/

/*
 * Procura uma string numa lista de strings.
 */
int elem(char** lista, char* key);

/*
 * Parte uma string aos bocados e coloca cada bocado numa posição do array.
 */
void linhaToArray(char* linha,char* tokensArray[7]);

/*
 * Conta quanto caracteres "x" existe numa string.
 */
int contaChar(Vendas* v, char x);

/* ----------------------------------- Funções da struct venda ----------------------------------*/

/*
 * Adiciona uma venda a uma estrutura de dados.
 */
void addVenda(Vendas* v, char* tokensArray[7], int index);

/*
 * Conta a maior linha da vendas.
 */
int contaMaiorLinha(char** listaVendas);

/*
 * Conta quantas vendas foram feitas por um cliente.
 */
int contaVendas(Vendas* v, char* cliente);

/*
 * Conta quantas quantas vendas foram feitas numa filial.
 */
int contaFilial(Vendas* v, int filial);

/*
 * Calcula faturação total registada.
 */
float contaFaturacao(Vendas*v);

/*
 * Conta quantos produtos foram comprados.
 */
int contaProdutosEnvolvidos(Vendas* vBoas);

/*
 * Conta quantos clientes efetuaram compras.
 */
int contaClientesEnvolvidos(Vendas* vBoas);

/* --------------------------- Parte de validação (apenas de uma linha) -------------------------*/

/*
 * Valida um cliente de acordo com a sua estrutura.
 */
int validaCliente(char* linha);

/*
 * Valida um produto de acordo com a sua estrutura.
 */
int validaProduto(char* linha);

/*
 * Valida uma venda.
 * Função de procura (elem) muito pouco eficiente.
 */
int validaVendas(char* tokensArray[7], char** listaProdutos, char** listaClientes);

/* --------------------------------- Parte de guardar nas listas --------------------------------*/

/*
 * Lê do ficheiro clientes e passa cada linha para um array de strings.
 * Passa para um array o elemento da primeira posição da linha lida, ou seja, a letra para ser contada.
 * Retorna o número de clientes válidos inseridos.
 */
int guardaClientes(FILE *fp, char** lista);

/*
 * Lê do ficheiro produtos e passa cada linha para um array de strings.
 * Retorna o número de produtos válidos inseridos.
 */
int guardaProdutos(FILE *fp, char** lista);

/*
 * Lê do ficheiro vendas.
 * Passa todas as linhas para uma struct de vendas "vTodas".
 * Passa apenas as linhas válidas para uma struct de vendas "vBoas".
 * Passa apenas as linhas válidas para o array de string "listaVendas".
 * Escreve num ficheiro de texto apenas as vendas válidas.
 * Retorna o número de vendas válidas.
 */
int guardaVendas(FILE *fp, char** listaVendas, char** listaProdutos, char** listaClientes, Vendas* vTodas, Vendas* vBoas);