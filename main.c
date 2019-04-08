#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "IO.h"

int main(int argc, char** argv) {

    clock_t start, end;
    double cpu_time_used;
    start = clock();

    Cat_Prods catp = inicializa_CatProds();
    Cat_Clientes catc = inicializa_CatClientes();
    Facturacao fat = inicializa_Facturacao();
    Filial fil[3];
    fil[0] = inicializa_Filial();
    fil[1] = inicializa_Filial();
    fil[2] = inicializa_Filial();

    SGV sgv = inicializa_SGV(catp,catc,fat,fil);

    int pLidos,cLidos,vLidas; pLidos = cLidos = vLidas = 0;
    List_Strings ls = initListaStrings();

    int query = 0;
    char c;
    while(query >= 0){

        query = runMenu();
        if(query == 1){
            char* file_nameProds = malloc(sizeof(char*));
            char* file_nameClient = malloc(sizeof(char*));
            char* file_nameVendas = malloc(sizeof(char*));

            inputQuery1(&file_nameProds,&file_nameClient,&file_nameVendas);
            int x = query1(sgv,file_nameProds,file_nameClient,file_nameVendas,&pLidos,&cLidos,&vLidas);
            outputQuery1(file_nameProds,file_nameClient,file_nameVendas,x,pLidos,cLidos,vLidas);
        }
        else if(query == 2 && vLidas != 0){
            c = inputQuery2();
            ls = query2(sgv,c);
            outputQuery2(ls);
        }
        else if(query == 3 && vLidas != 0){
            int nVendas = 0;
            float fat1T,fat1N,fat1P; fat1T = fat1N = fat1P = 0;
            float fat2T,fat2N,fat2P; fat2T = fat2N = fat2P = 0;
            float fat3T,fat3N,fat3P; fat3T = fat3N = fat3P = 0;
            char reader;
            int mes = 0;
            char* p = malloc(sizeof(char*));

            inputQuery3(&reader,&mes,&p);
            query3(sgv,mes,p,reader,&fat1T,&fat1N,&fat1P,&fat2T,&fat2N,&fat2P,&fat3T,&fat3N,&fat3P,&nVendas);
            outputQuery3(mes,p,reader,fat1T,fat1N,fat1P,fat2T,fat2N,fat2P,fat3T,fat3N,fat3P,nVendas);
        }
        else if(query == 4 && vLidas != 0){
            char c;
            int filial = 0;
            inputQuery4(&c,&filial);
            ls = query4(sgv,c,filial);
            outputQuery4(ls);
        }
        else if(query == 5 && vLidas != 0){
            ls = query5(sgv);
            outputQuery5(ls);
        }
        else if(query == 6 && vLidas != 0){
            int countC, countP; countC = countP = 0;
            query6(sgv,&countC,&countP);
            outputQuery6(countC,countP);
        }
        else if(query == 7 && vLidas != 0){
            int tabela[12][3];
            char* cliente = malloc(sizeof(char*));
            inputQuery7(&cliente);
            query7(sgv,cliente,tabela);
            outputQuery7(tabela);
        }
        else if(query == 8 && vLidas != 0){
            int totalVendas = 0;
            float totalFaturado = 0;
            int mes1,mes2; mes1 = mes2 = 0;
            inputQuery8(&mes1,&mes2);
            query8(sgv,mes1,mes2,&totalVendas,&totalFaturado);
            outputQuery8(mes1,mes2,totalVendas,totalFaturado);
        }
        else if(query == 9 && vLidas != 0){
            List_Strings lsN = initListaStrings();
            List_Strings lsP = initListaStrings();
            char* produto = malloc(sizeof(char*));
            int filial = 0;
            inputQuery9(&produto,&filial);
            query9(sgv,lsN,lsP,produto,filial);
            outputQuery9(lsN,lsP,produto,filial);
        }
        else if(query == 10 && vLidas != 0){
            char* cliente = malloc(sizeof(char*));
            int mes = 0;
            inputQuery10(&cliente,&mes);
            ls = query10(sgv,cliente,mes);
            outputQuery10(ls);
        }
        else if(query == 11 && vLidas != 0){
            List_Strings ls1 = initListaStrings();
            List_Strings ls2 = initListaStrings();
            List_Strings ls3 = initListaStrings();
            int count1,count2,count3; count1 = count2 = count3 = 0;
            int N = inputQuery11();
            query11(sgv,N,ls1,ls2,ls3,&count1,&count2,&count3);
            outputQuery11(ls1,ls2,ls3,count1,count2,count3,N);
        }
        else if(query == 12 && vLidas != 0){
            char* cliente = malloc(sizeof(char*));
            inputQuery12(&cliente);
            ls = query12(sgv,cliente);
            outputQuery12(ls);
        }
        else break;
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nCPU Time:%f segundos.\n\n", cpu_time_used);

    return 0;
}
