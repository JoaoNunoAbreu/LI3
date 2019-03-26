#include "Produto.h"
#include <stdio.h>
		
typedef struct cat_prods* Cat_Prods;
typedef struct lst_prods* Lista_Prods; 
		
Cat_Prods inicializa_CatProds();
Cat_Prods insereProd(Cat_Prods catp,Produto p);
int existeProd(Cat_Prods catp, Produto p);
void printCatProds(Cat_Prods cp);
 
Lista_Prods initListaProds();
Lista_Prods listaPorLetraP(Cat_Prods catp, char letra);
int sizeOfLista_Prods(Lista_Prods lp);
void printListaProds(Lista_Prods lp);

int guardaProdutos(FILE *fp, Cat_Prods catp);