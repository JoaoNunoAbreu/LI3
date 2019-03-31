#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "CatProds.h"
#include "CatClientes.h"
#include "Facturacao.h"
#include "SGV.h"

/* ----------------------------------- Funções da struct venda ----------------------------------*/

/**
 * Parte uma string aos bocados e coloca cada bocado numa posição do array.
 */
char** tokenizeLinhaVendaDyn(char* vendaRaw);

/**
 * Adiciona uma venda a uma estrutura de dados.
 */
Vendas mkVenda(char* linhaVenda);

/**
 * Conta a maior linha da vendas.
 */
int contaMaiorLinha(Vendas* v);

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

int validaVendas(char* linhaVenda, Cat_Prods catp, Cat_Clientes catc);

/* --------------------------------- Parte de guardar nas listas --------------------------------*/

/**
 * Lê do ficheiro vendas.
 * Passa todas as linhas para uma struct de vendas "vTodas".
 * Passa apenas as linhas válidas para uma struct de vendas "vBoas".
 * Passa apenas as linhas válidas para o array de string "listaVendas".
 * Escreve num ficheiro de texto apenas as vendas válidas.
 * Retorna o número de vendas válidas.
 */
int guardaVendas(FILE *fp, Cat_Prods catp, Cat_Clientes catc, Vendas* vTodas, Vendas* vBoas, Facturacao* f);