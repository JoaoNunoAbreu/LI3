#include "SGV.h"

struct sgv{
    Cat_Prods catp;
    Cat_Clientes catc;
    Facturacao fat;
    Filial filiais[3];
};

SGV inicializa_SGV(Cat_Prods catp, Cat_Clientes catc, Facturacao fat,Filial filiais[3]){
    SGV sgv = malloc(sizeof(struct sgv));
    sgv->catc = catc;
    sgv->catp = catp;
    sgv->fat = fat;
    sgv->filiais[0] = filiais[0];
    sgv->filiais[1] = filiais[1];
    sgv->filiais[2] = filiais[2];
    return sgv;
}

Cat_Prods getCatp(SGV sgv){
    return sgv->catp;
}

Cat_Clientes getCatc(SGV sgv){
    return sgv->catc;
}

Facturacao getFat(SGV sgv){
    return sgv->fat;
}

Filial* getFilial(SGV sgv){
    return sgv->filiais;
}

void setFat(SGV sgv, Facturacao fat){
    sgv->fat = fat;
}