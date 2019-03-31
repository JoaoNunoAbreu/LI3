#include "Facturacao.h"
#include "Pagina.h"

typedef struct sgv* SGV;

SGV inicializa_SGV(Cat_Prods catp, Cat_Clientes catc, Facturacao fat); /*Falta Filial filiais[3]*/

void query1(Cat_Prods catp, Cat_Clientes catc, Facturacao fat);
void query2(Cat_Prods catp);
void query3(SGV sgv,int mes, char* p);
/*void query4;
void query5;
void query6;
void query7;
void query8;
void query9;
void query10;
void query11;
void query12;*/