#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "CatProds.h"

typedef struct avlP{

    char* code;
    struct avlP *left,*right;
    int height;
}*AVLP;

struct cat_prods{
    AVLP array[26];
};

struct lst_prods{
    char** lista;
};

/*----------------------------------------------------------------*/

int heightP(AVLP a){ 
    if(a == NULL) return 0; 
    return a -> height; 
}
int maxP(int a, int b){ 
    return (a > b)? a : b; 
}
AVLP newNodeP(char* code){

    AVLP a = (AVLP) malloc(sizeof(struct avlP));
    a -> code = strdup(code);
    a -> left = NULL; 
    a -> right = NULL; 
    a -> height = 1;
    return a;
}
AVLP rightRotateP(AVLP y){ 
    
    AVLP x = y -> left; 
    AVLP T2 = x -> right; 
    x->right = y; 
    y->left = T2; 
    y->height = maxP(heightP(y->left), heightP(y->right))+1; 
    x->height = maxP(heightP(x->left), heightP(x->right))+1; 
    return x; 
}
AVLP leftRotateP(AVLP x){ 

    AVLP y = x -> right; 
    AVLP T2 = y -> left; 
    y -> left = x; 
    x -> right = T2; 
    x -> height = maxP(heightP(x->left), heightP(x->right))+1; 
    y -> height = maxP(heightP(y->left), heightP(y->right))+1; 
    return y; 
} 
int getBalanceP(AVLP N){ 
    if (N == NULL) return 0; 
    return heightP(N->left) - heightP(N->right); 
} 
AVLP insertP(AVLP node, char* code) { 

    if (node == NULL) return(newNodeP(code));
  
    if (strcmp(code,node->code) < 0) node -> left  = insertP(node->left,code); 
    else if (strcmp(code,node -> code) > 0) node->right = insertP(node->right,code); 
    else return node; 
  
    node -> height = 1 + maxP(heightP(node->left),heightP(node->right)); 

    int balance = getBalanceP(node); 
  
    /* Left Left Case */
    if (balance > 1 && strcmp(code,node->left->code) < 0) return rightRotateP(node); 
  
    /* Right Right Case */
    if (balance < -1 && strcmp(code,node->right->code) > 0) return leftRotateP(node); 
  
    /* Left Right Case */
    if (balance > 1 && strcmp(code,node->left->code) > 0){ 
        node->left = leftRotateP(node->left); 
        return rightRotateP(node); 
    } 
    /* Right Left Case */
    if (balance < -1 && strcmp(code,node->right->code) < 0){ 
        node->right = rightRotateP(node->right); 
        return leftRotateP(node); 
    } 
    return node; 
}
void preOrderP(AVLP root){ 
    if(root != NULL){ 
        printf("%s\n",root->code); 
        preOrderP(root->left); 
        preOrderP(root->right); 
    } 
}

int searchP(AVLP root,char* key){

    if(root == NULL) return 0;
    if(strcmp(key,root->code) < 0) return searchP(root->left,key);
    else if(strcmp(key,root->code) > 0) return searchP(root->right,key);
    else return 1;
}

/*----------------------------------------------------------------*/

int getIndexP(Produto p){
    return getChar0P(p) - 65;
}

Cat_Prods inicializa_CatProds(){
    Cat_Prods a = (Cat_Prods) malloc(sizeof(struct cat_prods));
    return a;
}

Cat_Prods insereProd(Cat_Prods catp, Produto p){

    int a = getIndexP(p);
    catp->array[a] = insertP(catp->array[a],getCodProd(p));
    return catp;
}

int existeProd(Cat_Prods catp, Produto p){
    return searchP(catp->array[getIndexP(p)],getCodProd(p));
}

void printCatProds(Cat_Prods cp){
    for(int i = 0; i < 26; i++)
        preOrderP(cp->array[i]);
}

// ------------------------------------------------------------------------------------------------

Lista_Prods preOrderPLista(AVLP root, Lista_Prods lp,int index){
    if(root != NULL){ 
        lp->lista[index] = strdup(root->code);
        preOrderPLista(root->left,lp,index+6);
        preOrderPLista(root->right,lp,index+12); 
    }
    return lp;
}

Lista_Prods initListaProds(){
    Lista_Prods lista = (Lista_Prods) malloc(sizeof(struct lst_prods));
    char** campos = (char**) malloc(200000 * sizeof(char*));
    lista->lista = campos;
    return lista;
}

Lista_Prods listaPorLetra(Cat_Prods catp, char letra){
    int posicao = letra - 65;
    Lista_Prods lp = initListaProds();
    lp = preOrderPLista(catp->array[posicao],lp,0);
    return lp;
}

void printListaProds(Lista_Prods lp){
    for(int i = 0; lp->lista[i]; i++)
        printf("%s\n",lp->lista[i]);
}

// ------------------------------------------------------------------------------------------------

int validaProduto(Produto p){

    int r = 1;
    char* linha = getCodProd(p);
    if(linha == NULL || strlen(linha) != 6) return 0;

    if(!isupper(linha[0]) || !isupper(linha[1])) r = 0;
    else{
        int num1 = atoi(linha+2);
        if(num1 < 1000 || num1 > 9999) r = 0;
    }
    return r;
}

int guardaProdutos(FILE *fp, Cat_Prods catp){

    char str[7];
    char* linha;
    int index = 0;
    while(fgets(str,7,fp)){
        linha = strtok(str,"\n\r");
        Produto p = criaProd(linha);
        if(validaProduto(p)){
            catp = insereProd(catp,p);
            index++;
        }
    }
    return index;
}