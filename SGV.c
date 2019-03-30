#include "CatProds.h"
#include "CatClientes.h"
#include "Facturacao.h"
#include "SGV.h"

struct sgv{
    Cat_Prods catp;
    Cat_Clientes catc;
    //Filial filiais[3];
    Facturacao fat;
};

SGV inicializa_SGV(Cat_Prods catp, Cat_Clientes catc, Facturacao fat){ /*Falta Filial filiais[3]*/
    SGV sgv = malloc(sizeof(struct sgv));
    sgv->catc = catc;
    sgv->catp = catp;
    sgv->fat = fat;
    return sgv;
}

void query3(SGV sgv,int mes, char* p){
    int nVendas = 0;
    int reader = 0; // Leitor da opção do user

    float facturadoTotal ,facturadoN ,facturadoP ; facturadoTotal  = facturadoN  = facturadoP  = 0;
    float facturado1Total,facturado1N,facturado1P; facturado1Total = facturado1N = facturado1P = 0;
    float facturado2Total,facturado2N,facturado2P; facturado2Total = facturado2N = facturado2P = 0;
    float facturado3Total,facturado3N,facturado3P; facturado3Total = facturado3N = facturado3P = 0;


    Nodo n = editNodo(mes,p);
    sgv->fat = searchF(sgv->fat,n);
    if(sgv->fat != NULL){ // Se for NULL significa que não encontrou
        Info i = getInfo(sgv->fat);

        printf("Resultado global ou filial a filial? (1/2)\n");
        scanf("%d",&reader);

        while(i != NULL){
            if(mes == getMes(i)){
                if(reader == 1) {
                    facturadoTotal += getPreco(i) * getQuant(i);
                    if(getPromo(i) == 'N') facturadoN += getPreco(i) * getQuant(i);
                    if(getPromo(i) == 'P') facturadoP += getPreco(i) * getQuant(i);
                }
                else{
                    if(getFilial(i) == 1) {
                        facturado1Total += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'N') facturado1N += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'P') facturado1P += getPreco(i) * getQuant(i);
                    }
                    if(getFilial(i) == 2){
                        facturado2Total += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'N') facturado2N += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'P') facturado2P += getPreco(i) * getQuant(i);
                    }
                    if(getFilial(i) == 3){
                        facturado3Total += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'N') facturado3N += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'P') facturado3P += getPreco(i) * getQuant(i);
                    }
                }
                nVendas++;   
            }
            i = getInfoNext(i);
        }
    }
    printf("Para o produto %s no mês %d, os resultados são os seguintes:\n",p,mes);
    printf("O número total de vendas foi: %d\n",nVendas);
    if(reader == 1) {
        printf("A faturação total foi: %f\n", facturadoTotal);
        printf("A faturação em modo N foi: %f\n", facturadoN);
        printf("A faturação em modo P foi: %f\n", facturadoP);
    }
    else {
        printf("Filial Facturação 1: %f\n",facturado1Total);
        printf("Filial Facturação 1 em modo N : %f\n",facturado1N);
        printf("Filial Facturação 1 em modo P : %f\n",facturado1P);
        printf("Filial Facturação 2: %f\n",facturado2Total);
        printf("Filial Facturação 2 em modo N : %f\n",facturado2N);
        printf("Filial Facturação 2 em modo P : %f\n",facturado2P);
        printf("Filial Facturação 3: %f\n",facturado3Total);
        printf("Filial Facturação 3 em modo N : %f\n",facturado3N);
        printf("Filial Facturação 3 em modo P : %f\n",facturado3P);
    }
}

/*void query5(SGV sgv){
    while(getFilial()){
        Lista_Clientes = ...;
    }
}*/