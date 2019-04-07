#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "Queries.h"
#include "IO.h"

int main(int argc, char** argv) {

    /* -------------------------------------- Medição Texec -------------------------------------*/

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

    printf("-------------------------- Início ------------------------------\n\n");

    int x = runMenu();
    if(x == 1){
        char* file_nameProds = NULL;
        char* file_nameClient = NULL;
        char* file_nameVendas = NULL;
        int pLidos,cLidos,vLidas; pLidos = cLidos = vLidas = 0;

        inputQuery1(&file_nameProds,&file_nameClient,&file_nameVendas);
        int x = query1(sgv,file_nameProds,file_nameClient,file_nameVendas,&pLidos,&cLidos,&vLidas);
        printf("%d\n",x);
        printf("%s\n",file_nameProds);
        printf("%s\n",file_nameClient);
        printf("%s\n",file_nameVendas);
        outputQuery1(file_nameProds,file_nameClient,file_nameVendas,x,pLidos,cLidos,vLidas);
    }
    //query1(sgv);
    //query2(sgv);
    //query3(sgv,2,"KR1583");
    //query4(sgv);
    //query5(sgv);
    //query6(sgv);
    //query7(sgv,"K4984");
    //query8(sgv,5,9);
    //query9(sgv,"DV1293",1);
    //query10(sgv,"Q3869",9);
    //query11(sgv,3);
    //query12(sgv,"Q3869");

    printf("\n--------------------------- Fim --------------------------------\n");

    /* ------------------------------------- Medição Texec --------------------------------------*/

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nCPU Time:%f segundos.\n\n", cpu_time_used);

    return 0;
}
