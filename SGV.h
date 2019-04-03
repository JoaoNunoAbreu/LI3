#include "Facturacao.h"
#include "Filial.h"
#include "Pagina.h"

typedef struct sgv* SGV;

SGV inicializa_SGV(Cat_Prods catp, Cat_Clientes catc, Facturacao fat,Filial filiais[3]);
Cat_Prods getCatp(SGV sgv);
Cat_Clientes getCatc(SGV sgv);
Facturacao getFat(SGV sgv);
Filial* getFilial(SGV sgv);
void setFat(SGV sgv, Facturacao fat);