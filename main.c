#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "SGV.h"

int main(int argc, char** argv) {

    /* -------------------------------------- Medição Texec -------------------------------------*/

    clock_t start, end;
    double cpu_time_used;
    start = clock();

    Cat_Prods catp = inicializa_CatProds();
    Cat_Clientes catc = inicializa_CatClientes();
    Facturacao fat = inicializa_Facturacao();

    printf("-------------------------- Início ------------------------------\n\n");

    query1(catp,catc,fat);
    SGV sgv = inicializa_SGV(catp,catc,fat);

    query2(catp);

    

    /* ------------------------------------------ TESTES ----------------------------------------*/

    printf("\n");

    /*printf("A linha mais longa das vendas foi: %d\n", contaMaiorLinha(listaVendas));
    int prodEnvolvidos = contaProdutosEnvolvidos(vBoas);
    printf("O número de produtos envolvidos foi: %d\n", prodEnvolvidos);
    printf("O número de produtos nunca comprado foi: %d\n", pLidos - prodEnvolvidos);
    int clientEnvolvidos = contaClientesEnvolvidos(vBoas);
    printf("O número de clientes envolvidos foi: %d\n",clientEnvolvidos);
    printf("O número de clientes nunca comprado foi: %d\n",cLidos - clientEnvolvidos);
    printf("Houve %d códigos de clientes inválidos nas vendas.\n",indexCI);
    printf("Houve %d códigos de produtos inválidos nas vendas.\n",indexPI);
    printf("O último cliente (válido) foi: %s\n",vBoas[vLidas-1].cliente);
    printf("Este cliente fez %d vendas\n",contaVendas(vBoas,vBoas[vLidas-1].cliente));
    printf("Foram feitas %d vendas na filial 1\n",contaFilial(vBoas,1));
    printf("Foram feitas %d vendas na filial 2\n",contaFilial(vBoas,2));
    printf("Foram feitas %d vendas na filial 3\n",contaFilial(vBoas,3));
    printf("A faturação total foi: %e\n",contaFaturacao(vBoas));
    printf("Foram vendidas %d unidades.\n",contaUnidades(vBoas));
    printf("Foram feitas %d vendas com preço 0.\n",contaPrecos(vBoas,0));
    printf("\n");*/

    printf("--------------------------- Fim --------------------------------\n");

    /* ------------------------------------- Medição Texec --------------------------------------*/

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nCPU Time:%f segundos.\n\n", cpu_time_used);

    return 0;
}
