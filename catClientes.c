#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatClientes.h"

typedef struct avlC{

    char* code;
    struct avlC *left,*right;
    int height;
}*AVLC;

struct cat_clientes{
    AVLC array[26];
};

struct lst_clientes{
    char** lista;
};

/*----------------------------------------------------------------*/

int heightC(AVLC a){ 
    if(a == NULL) return 0; 
    return a -> height; 
}
int maxC(int a, int b){ 
    return (a > b)? a : b; 
}
AVLC newNodeC(char* code){

    AVLC a = (AVLC) malloc(sizeof(struct avlC));
    a -> code = strdup(code);
    a -> left = NULL; 
    a -> right = NULL; 
    a -> height = 1;
    return a;
}
AVLC rightRotateC(AVLC y){ 
    
    AVLC x = y -> left; 
    AVLC T2 = x -> right; 
    x->right = y; 
    y->left = T2; 
    y->height = maxC(heightC(y->left), heightC(y->right))+1; 
    x->height = maxC(heightC(x->left), heightC(x->right))+1; 
    return x; 
}
AVLC leftRotateC(AVLC x){ 

    AVLC y = x -> right; 
    AVLC T2 = y -> left; 
    y -> left = x; 
    x -> right = T2; 
    x -> height = maxC(heightC(x->left), heightC(x->right))+1; 
    y -> height = maxC(heightC(y->left), heightC(y->right))+1; 
    return y; 
} 
int getBalanceC(AVLC N){ 
    if (N == NULL) return 0; 
    return heightC(N->left) - heightC(N->right); 
} 
AVLC insertC(AVLC node, char* code) { 

    if (node == NULL) return(newNodeC(code));
  
    if (strcmp(code,node->code) < 0) node -> left  = insertC(node->left,code); 
    else if (strcmp(code,node -> code) > 0) node->right = insertC(node->right,code); 
    else return node; 
  
    node -> height = 1 + maxC(heightC(node->left),heightC(node->right)); 

    int balance = getBalanceC(node); 
  
    /* Left Left Case */
    if (balance > 1 && strcmp(code,node->left->code) < 0) return rightRotateC(node); 
  
    /* Right Right Case */
    if (balance < -1 && strcmp(code,node->right->code) > 0) return leftRotateC(node); 
  
    /* Left Right Case */
    if (balance > 1 && strcmp(code,node->left->code) > 0){ 
        node->left = leftRotateC(node->left); 
        return rightRotateC(node); 
    } 
    /* Right Left Case */
    if (balance < -1 && strcmp(code,node->right->code) < 0){ 
        node->right = rightRotateC(node->right); 
        return leftRotateC(node); 
    } 
    return node; 
}
void preOrderC(AVLC root){ 
    if(root != NULL){ 
        printf("%s\n",root->code); 
        preOrderC(root->left); 
        preOrderC(root->right); 
    } 
}
int searchC(AVLC root,char* key){

    if(root == NULL) return 0;
    if(strcmp(key,root->code) < 0) return searchC(root->left,key);
    else if(strcmp(key,root->code) > 0) return searchC(root->right,key);
    else return 1;
}

/*----------------------------------------------------------------*/

int getIndexC(Cliente c){
    return getChar0C(c) - 65;
}

Cat_Clientes inicializa_CatClientes(){
    Cat_Clientes a = (Cat_Clientes) malloc(sizeof(struct cat_clientes));
    return a;
}

Cat_Clientes insereCliente(Cat_Clientes catp, Cliente c){

    int a = getIndexC(c);
    catp->array[a] = insertC(catp->array[a],getCodCliente(c));
    return catp;
}

int existeCliente(Cat_Clientes catp, Cliente p){
    return searchC(catp->array[getIndexC(p)],getCodCliente(p));
}

void printCatCliente(Cat_Clientes cp){
    for(int i = 0; i < 26; i++)
        preOrderC(cp->array[i]);
}