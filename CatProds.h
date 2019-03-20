#include "Produto.h"
		
typedef struct cat_prods* Cat_Prods;
typedef struct lst_prods* Lista_Prods; 
		
Cat_Prods inicializa_CatProds();
Cat_Prods insereProd(Cat_Prods catp,Produto p);
int existeProd(Cat_Prods catp, Produto p);
void printCatProds(Cat_Prods cp);
 
Lista_Prods initListaProds();
Lista_Prods listaPorLetra(Cat_Prods catp, char letra);
void printListaProds(Lista_Prods lp);

/**
 * Valida um produto de acordo com a sua estrutura.
 */
int validaProdutoP(Produto p);
/**
 * Lê do ficheiro produtos e passa cada linha para o catálogo de produtos.
 * Retorna o número de produtos válidos inseridos.
 */
int guardaProdutosP(FILE *fp, Cat_Prods catp);