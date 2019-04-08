#include <stdio.h>
#include <stdlib.h>
#include "IO.h"

int runMenu(){
    int reader = 0;
    printf("\n-------------------------- Início ------------------------------\n\n");
    printf("Que query pretende executar? (Inserir número <= 0 para sair) \n");
    printf("Query 1 - Ler os 3 ficheiros.\n");
    printf("Query 2 - Lista de produtos que começam por uma letra.\n");
    printf("Query 3 - Mês/código -> num vendas e total facturado.\n");
    printf("Query 4 - Lista produtos ordenados que ninguém comprou.\n");
    printf("Query 5 - Lista de clientes compraram nas 3 filiais.\n");
    printf("Query 6 - Produtos e clientes não utilizados.\n");
    printf("Query 7 - Cliente -> tabela produtos comprados por filial.\n");
    printf("Query 8 - Intervalo meses -> total vendas e facturado.\n");
    printf("Query 9 - Produto/filial -> clientes que o compraram em N e P.\n");
    printf("Query 10 - Cliente/mês -> lista de produtos que mais compraram ordem descendente.\n");
    printf("Query 11 - Lista dos N produtos mais vendidos em todo o ano\n");
    printf("Query 12 - Cliente -> 3 produtos em que gastou mais dinheiro.\n\n");
    printf("-------------------------- Fim ------------------------------\n");
    
    scanf(" %d",&reader);
    return reader;
}

void inputQuery1(char** file_nameProds, char** file_nameClient, char** file_nameVendas){

    char c;
    printf("Pretende inserir nome do ficheiro de Produtos? (s/n)\n");
    scanf(" %c",&c);
    if(c == 's'){
        printf("Nome do ficheiros com produtos: \n");
        scanf("%s",*file_nameProds);
        *file_nameProds = pwd(*file_nameProds);
    }
    else if(c == 'n') *file_nameProds = pwd("Produtos.txt");
    else {printf("Char inserido inválido\n");exit(1);}


    printf("Pretende inserir nome do ficheiro de Clientes? (s/n)\n");
    scanf(" %c",&c);
    if(c == 's'){
        printf("Nome do ficheiros com clientes: \n");
        scanf("%s",*file_nameClient);
        *file_nameClient = pwd(*file_nameClient);
    }
    else if(c == 'n') *file_nameClient = pwd("Clientes.txt");
    else {printf("Char inserido inválido\n");exit(1);}


    printf("Pretende inserir nome do ficheiro de Vendas? (s/n)\n");
    scanf(" %c",&c);
    if(c == 's'){
        printf("Nome do ficheiros com vendas: \n");
        scanf("%s",*file_nameVendas);
        *file_nameVendas = pwd(*file_nameVendas);
    }
    else if(c == 'n') *file_nameVendas = pwd("FicheirosTeste/testeVendas2.txt");
    else {printf("Char inserido inválido\n");exit(1);}
}

void outputQuery1(char* file_nameProds,char* file_nameClient,char* file_nameVendas,int x,int pLidos,int cLidos,int vLidas){
    if(x == 1) {printf("Ficheiro %s não foi possível ser carregado.\n",file_nameProds);exit(1);}
    else if(x == 2) {printf("Ficheiro %s não foi possível ser carregado.\n",file_nameClient);exit(1);}
    else if(x == 3) {printf("Ficheiro %s não foi possível ser carregado.\n",file_nameVendas);exit(1);}
    else{
        printf("Ficheiro %s foi carregado com sucesso.\n",file_nameProds);
        printf("Ficheiro %s foi carregado com sucesso.\n",file_nameClient);
        printf("Ficheiro %s foi carregado com sucesso.\n",file_nameVendas);
        
        printf("Foram lidas %d linhas válidas do ficheiro dos produtos.\n",pLidos);
        printf("Foram lidas %d linhas válidas do ficheiro dos clientes.\n",cLidos);
        printf("Foram lidas %d linhas válidas do ficheiro dos vendas.\n",vLidas);
    }
}

// ------------------------------------------------------------------------------------------------

char inputQuery2(){
    char c;
    printf("Insira uma letra para determinar a lista e o nº total de produtos cujo código se inicia por essa letra\n");
    scanf(" %c",&c);
    return c;
}

void outputQuery2(List_Strings ls){    
    navegador(ls);
    printf("O número total de produtos é: %d\n",sizeList_Strings(ls));
}

// ------------------------------------------------------------------------------------------------

void inputQuery3(char* reader, int* mes, char** p){
    printf("Resultado global ou filial a filial? (g/f)\n");
    scanf(" %c",reader);
    printf("Nome do produto:\n");
    scanf(" %s",*p);
    printf("Número do mês:\n");
    scanf(" %d",mes);
}

void outputQuery3(int mes, char* p, char c,float fat1T,float fat1N,float fat1P,float fat2T,float fat2N,float fat2P, float fat3T,float fat3N,float fat3P, int nVendas){

    if(nVendas != 0){
        printf("Para o produto %s no mês %d, os resultados são os seguintes:\n",p,mes);
        printf("O número total de vendas foi: %d\n",nVendas);
        if(c == 'g') {
            printf("A faturação total foi: %f\n", fat1T);
            printf("A faturação em modo N foi: %f\n", fat1N);
            printf("A faturação em modo P foi: %f\n", fat1P);
        }
        else if(c == 'f') {
            printf("Filial Facturação 1: %f\n",fat1T);
            printf("Filial Facturação 1 em modo N : %f\n",fat1N);
            printf("Filial Facturação 1 em modo P : %f\n",fat1P);
            printf("Filial Facturação 2: %f\n",fat2T);
            printf("Filial Facturação 2 em modo N : %f\n",fat2N);
            printf("Filial Facturação 2 em modo P : %f\n",fat2P);
            printf("Filial Facturação 3: %f\n",fat3T);
            printf("Filial Facturação 3 em modo N : %f\n",fat3N);
            printf("Filial Facturação 3 em modo P : %f\n",fat3P);
        }
        else printf("Char inserido inválido\n");
    }
    else printf("Não foram encontradas vendas onde o produto %s foi comprado no mês %d",p,mes);
}

// ------------------------------------------------------------------------------------------------

void inputQuery4(char* c, int* filial){

    printf("Valores totais ou divididos pelas filiais? (t/f)\n");
    scanf(" %c",c);
    if(*c != 't' && *c != 'f') {printf("Char inserido inválido.\n");exit(0);}
    if(*c == 'f'){
        printf("Qual é a filial?\n");
        scanf(" %d",filial);
    }
}

void outputQuery4(List_Strings ls){
    navegador(ls);
    printf("O número total de produtos é: %d\n",sizeList_Strings(ls));
}

// ------------------------------------------------------------------------------------------------

void outputQuery5(List_Strings ls){
    navegador(ls);
    printf("O número de códigos de clientes que realizaram compras em todas as filiais é: %d.\n",sizeList_Strings(ls));
}

// ------------------------------------------------------------------------------------------------

void outputQuery6(int countC, int countP){
    printf("Nº clientes que não realizaram compras: %d\n",countC);
    printf("Nº de produtos que ninguém comprou: %d\n",countP);
}

// ------------------------------------------------------------------------------------------------

void inputQuery7(char** reader){
    printf("Código do cliente:\n");
    scanf(" %s",*reader);
}

void outputQuery7(int tabela[12][3]){
    printf("\nMeses - Linhas\n");
    printf("Filiais - Colunas\n\n");
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 3; j++)
            if(j == 2) printf("%d",tabela[i][j]);
            else if(j == 0) printf("     %d, ",tabela[i][j]);
            else printf("%d, ",tabela[i][j]);
        printf("\n");
    }
}

// ------------------------------------------------------------------------------------------------

void inputQuery8(int* mes1, int* mes2){
    printf("Primeiro mês:\n");
    scanf(" %d",mes1);
    printf("Segundo mês:\n");
    scanf(" %d",mes2);
}

void outputQuery8(int mes1, int mes2, int totalVendas, float totalFaturado){
    printf("O total de vendas entre os meses %d e %d foi: %d.\n",mes1,mes2,totalVendas);
    printf("O total faturado entre os meses %d e %d foi: %f.\n",mes1,mes2,totalFaturado);
}

// ------------------------------------------------------------------------------------------------

void inputQuery9(char** produto, int* filial){
    printf("Código do produto:\n");
    scanf(" %s",*produto);
    printf("Número da filial:\n");
    scanf(" %d",filial);
    if(*filial < 1 || *filial > 3){printf("Número da filial introduzida é inválida\n"); exit(1);}
}

void outputQuery9(List_Strings lsN, List_Strings lsP, char* produto, int filial){
    printf("Lista dos clientes que compraram o produto %s na filial %d com promoção N\n",produto,filial);
    navegador(lsN);
    printf("Tamanho da lista N: %d\n",sizeList_Strings(lsN));

    printf("Lista dos clientes que compraram o produto %s na filial %d com promoção P\n",produto,filial);
    navegador(lsP);
    printf("Tamanho da lista P: %d\n",sizeList_Strings(lsP));
}

// ------------------------------------------------------------------------------------------------

void inputQuery10(char** cliente,int* mes){
    printf("Código do cliente:\n");
    scanf(" %s",*cliente);
    printf("Número do mês:\n");
    scanf(" %d",mes);
}

void outputQuery10(List_Strings ls){
    navegador(ls);
}
// ------------------------------------------------------------------------------------------------

int inputQuery11(){
    int N = 0;
    printf("Valor de N:\n");
    scanf(" %d",&N);
    return N;
}

void outputQuery11(List_Strings ls1,List_Strings ls2, List_Strings ls3, int count1, int count2, int count3, int N){

    printf("---- Filial 1 ----\n");
    printNList(ls1,N);
    printf("%d\n",count1);
    printf("---- Filial 2 ----\n");
    printNList(ls2,N);
    printf("%d\n",count2);
    printf("---- Filial 3 ----\n");
    printNList(ls3,N);
    printf("%d\n",count3);
}

// ------------------------------------------------------------------------------------------------

void inputQuery12(char** cliente){
    printf("Código do cliente:\n");
    scanf(" %s",*cliente);
}

void outputQuery12(List_Strings ls){
    navegador(ls);
}