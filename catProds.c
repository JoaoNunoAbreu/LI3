#include "AVL.h"
#include "CatProds.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct cat_prods{
    AVL array[26];
};

struct lst_prods{
    char** lista;
};

/*----------------------------------------- Catálogo --------------------------------------------*/

int getIndexP(Produto p){
    return getChar0P(p) - 65;
}

Cat_Prods inicializa_CatProds(){
    Cat_Prods catp = (Cat_Prods) malloc(sizeof(struct cat_prods));
    for(int i = 0; i < 26;i++)
        catp->array[i] = NULL;
    return catp;
}

Cat_Prods insereProd(Cat_Prods catp, Produto p){

    int a = getIndexP(p);
    char* linha = getCodProd(p);
    catp->array[a] = insert(catp->array[a],linha);
    return catp;
}

int existeProd(Cat_Prods catp, Produto p){
    return search(catp->array[getIndexP(p)],getCodProd(p));
}

void printCatProds(Cat_Prods cp){
    for(int i = 0; i < 26; i++)
        preOrder(cp->array[i]);
}

/* ------------------------------------------- Lista ------------------------------------------- */

Lista_Prods inOrderPLista(AVL root, Lista_Prods lp,int* index){
    if(root != NULL){ 
        inOrderPLista(getLeft(root),lp,index);
        lp->lista[*index] = strdup(getCode(root));
        *index = *index + 1;
        inOrderPLista(getRight(root),lp,index); 
    }
    return lp;
}

Lista_Prods initListaProds(){
    Lista_Prods lp = (Lista_Prods) malloc(sizeof(struct lst_prods));
    char** campos = (char**) malloc(200000 * sizeof(char*));
    lp->lista = campos;
    return lp;
}

Lista_Prods listaPorLetraP(Cat_Prods catp, char letra){
    int posicao = letra - 65;
    Lista_Prods lp = initListaProds();
    int inx = 0;
    lp = inOrderPLista(catp->array[posicao],lp,&inx);
    return lp;
}

char** getListaProds(Lista_Prods lp){
    return lp->lista;
}

void printListaProds(Lista_Prods lp){
    for(int i = 0; lp->lista[i]; i++)
        printf("%s\n",lp->lista[i]);
}

/* ------------------------------------------------------------------------------------------------*/

int guardaProdutos(FILE *fp, Cat_Prods catp){

    char str[8];
    char* linha;
    int index = 0;
    while(fgets(str,8,fp)){
        linha = strtok(str,"\n\r");
        Produto p = criaProd(linha);
        if(validaProduto(p)){
            catp = insereProd(catp,p);
            index++;
        }
    }
    return index;
}