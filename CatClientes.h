#include "Cliente.h"
		
typedef struct cat_clientes* Cat_Clientes;
typedef struct lst_clientes* Lista_Cliente; 
		
Cat_Clientes inicializa_CatProds();
Cat_Clientes insereProd(Cat_Clientes catc,Cliente p);
int existeProd(Cat_Clientes catc, Cliente p);
void printCatProds(Cat_Clientes cp);
 
/*Lista_Prods listaPorLetra(Cat_Clientes catp, char letra);
Lista_Prods initListaProds();*/