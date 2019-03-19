#include "Produto.h"
		
typedef struct cat_prods* Cat_Prods;
typedef struct lst_prods* Lista_Prods; 
		
Cat_Prods inicializa_CatProds();
Cat_Prods insereProd(Cat_Prods catp,Produto p);
int existeProd(Cat_Prods catp, Produto p);
void printCatProds(Cat_Prods cp);
 
/*Lista_Prods listaPorLetra(Cat_Prods catp, char letra);
Lista_Prods initListaProds();*/