#include "CatProds.h"
#include "CatClientes.h"

typedef struct sgv{
    Cat_Prods catp;
    Cat_Clientes catc;
    Filial filiais[NUM];
    Faturacao fat;
}*SGV;

void query5(SGV sgv){
    while(getFilial()){
        Lista_Clientes = ...;
    }
}