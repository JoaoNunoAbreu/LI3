#include "Produto.h"
		
typedef struct cat_prods* Cat_Prods;
typedef struct lst_prods* Lista_Prods; 

char getIndex(Produto p, int index);		
Cat_Prods inicializa_CatProds();
Cat_Prods insereProd(Cat_Prods catp,Produto p);
/*int existeProd(Cat_Prods catp, Produto p);
 
Lista_Prods listaPorLetra(Cat_Prods catp, char letra);
Lista_Prods initListaProds();*/