#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAXVENDAS 1000000
#define MAXBUFPROD 7
#define MAXBUFCLIENT 6
#define MAXBUFVENDAS 32

typedef struct venda{
    char *produto;
    float preco;
    int quant;
    char *promo;
    char *cliente;
    int mes;
    int filial;
}Vendas;

typedef struct avlPC{

    char* code;
    struct avlPC *left,*right;
    int height;
}*AVLPC;

char* listaVendas[MAXVENDAS];

char* clientesInvalidos[MAXVENDAS]; int indexCI;
char* produtosInvalidos[MAXVENDAS]; int indexPI;

/* -------------------------------------- Funções das AVL ---------------------------------------*/

/**
 * Calcula a altura de uma AVL.
 */ 
int heightPC(AVLPC a);
/**
 * Calcula o máximo entre 2 números.
 */
int max(int a, int b);
/**
 * Cria um novo nodo dado um código de cliente/produto.
 */
AVLPC newNode(char* code);
/**
 * Roda a AVL para a direita para fins de balançeamento.
 */
AVLPC rightRotate(AVLPC y);
/**
 * Roda a AVL para a esquerda para fins de balançeamento.
 */
AVLPC leftRotate(AVLPC x);
/**
 * Calcula o balanço de uma AVL.
 */
int getBalance(AVLPC N);
/**
 * Insere numa AVL um código de cliente/produto.
 */
AVLPC insert(AVLPC node, char* code);
/**
 * Faz print de uma AVL em pre-order.
 */
void preOrder(AVLPC root);
/**
 * Procura numa AVL um código.
 */
int search(AVLPC root,char* key);

/* ----------------------------------- Funções da struct venda ----------------------------------*/

/**
 * Parte uma string aos bocados e coloca cada bocado numa posição do array.
 */
char** tokenizeLinhaVendaDyn(char* vendaRaw);

/**
 * Conta quanto caracteres "x" existe numa string.
 */
int contaChar(Vendas* v, char x);

/**
 * Adiciona uma venda a uma estrutura de dados.
 */
Vendas mkVenda(char* linhaVenda);

/**
 * Conta a maior linha da vendas.
 */
int contaMaiorLinha(char** listaVendas);

/**
 * Conta quantas vendas foram feitas por um cliente.
 */
int contaVendas(Vendas* v, char* cliente);

/**
 * Conta quantas quantas vendas foram feitas numa filial.
 */
int contaFilial(Vendas* v, int filial);

/**
 * Calcula faturação total registada.
 */
float contaFaturacao(Vendas*v);

/**
 * Conta quantos preços forem iguais a "x"
 */
int contaPrecos(Vendas* v, int x);

/**
 * Conta quantos produtos foram comprados.
 */
int contaProdutosEnvolvidos(Vendas* v);

/**
 * Conta quantos clientes efetuaram compras.
 */
int contaClientesEnvolvidos(Vendas* v);

/**
 * Conta quantas unidades foram vendidas.
 */
int contaUnidades(Vendas* v);

/* --------------------------- Parte de validação (apenas de uma linha) -------------------------*/
int validaProduto(char* linha);
/**
 * Valida um cliente de acordo com a sua estrutura.
 */
int validaCliente(char* linha);

/**
 * Valida uma venda.
 * Função de procura (elem) muito pouco eficiente.
 */
int validaVendas(char* linhaVenda, AVLPC rootP, AVLPC rootC);

/* --------------------------------- Parte de guardar nas listas --------------------------------*/

int guardaProdutos(FILE *fp, AVLPC *root);
/**
 * Lê do ficheiro clientes e passa cada linha para um array de strings.
 * Passa para um array o elemento da primeira posição da linha lida, ou seja, a letra para ser contada.
 * Retorna o número de clientes válidos inseridos.
 */
int guardaClientes(FILE *fp, AVLPC* a);



/**
 * Lê do ficheiro vendas.
 * Passa todas as linhas para uma struct de vendas "vTodas".
 * Passa apenas as linhas válidas para uma struct de vendas "vBoas".
 * Passa apenas as linhas válidas para o array de string "listaVendas".
 * Escreve num ficheiro de texto apenas as vendas válidas.
 * Retorna o número de vendas válidas.
 */
int guardaVendas(FILE *fp, char** listaVendas, AVLPC rootP, AVLPC rootC, Vendas* vTodas, Vendas* vBoas);