#include "Filial.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Lista de clientes de um produto e respectivas quantidades
struct infofil{
    char* produto;
    float preco;
    int quant;
    char promo;
    int mes;
    struct infofil *next;
};

// Estrutura AVL onde são guardados os dados finais das filiais
struct avlFilial{
    NodoFil n;
    struct avlFilial *left,*right;
    int height;
};

// ------------------------------------------------------------------------------------------------

int heightFi(Filial a){ 
    if(a == NULL) return 0; 
    return a -> height; 
}
int maxFi(int a, int b){ 
    return (a > b)? a : b; 
}
Filial newNodeFi(NodoFil n){

    Filial a = (Filial) malloc(sizeof(struct avlFilial));
    a -> n = n;
    a -> left = NULL; 
    a -> right = NULL; 
    a -> height = 1;
    return a;
}
Filial rightRotateFi(Filial y){ 
    
    Filial x = y -> left; 
    Filial T2 = x -> right; 
    x->right = y; 
    y->left = T2; 
    y->height = maxFi(heightFi(y->left), heightFi(y->right))+1; 
    x->height = maxFi(heightFi(x->left), heightFi(x->right))+1; 
    return x; 
}
Filial leftRotateFi(Filial x){ 

    Filial y = x -> right; 
    Filial T2 = y -> left; 
    y -> left = x; 
    x -> right = T2; 
    x -> height = maxFi(heightFi(x->left), heightFi(x->right))+1; 
    y -> height = maxFi(heightFi(y->left), heightFi(y->right))+1; 
    return y; 
} 
int getBalanceFi(Filial N){ 
    if (N == NULL) return 0; 
    return heightFi(N->left) - heightFi(N->right); 
} 

Filial insertFi(Filial node, NodoFil n){ 

    if (node == NULL) return(newNodeFi(n));

    if (strcmp(n.cliente,node->n.cliente) < 0) node -> left  = insertFi(node->left,n); 
    else if (strcmp(n.cliente,node -> n.cliente) > 0) node->right = insertFi(node->right,n); 
    else{
        node->n.i = n.i;
        return node; 
    }
  
    node -> height = 1 + maxFi(heightFi(node->left),heightFi(node->right)); 

    int balance = getBalanceFi(node);
  
    // Left Left Case 
    if (balance > 1 && strcmp(n.cliente,node->left->n.cliente) < 0) return rightRotateFi(node); 
  
    // Right Right Case
    if (balance < -1 && strcmp(n.cliente,node->right->n.cliente) > 0) return leftRotateFi(node); 
  
    // Left Right Case
    if (balance > 1 && strcmp(n.cliente,node->left->n.cliente) > 0){ 
        node->left = leftRotateFi(node->left); 
        return rightRotateFi(node); 
    } 
    // Right Left Case
    if (balance < -1 && strcmp(n.cliente,node->right->n.cliente) < 0){ 
        node->right = rightRotateFi(node->right); 
        return leftRotateFi(node); 
    } 
    return node; 
}
void inOrderFi(Filial root){ 
    if(root != NULL){ 
        inOrderFi(root->left);
        printf("%s\n",root->n.cliente); 
        inOrderFi(root->right); 
    } 
}
int searchFi(Filial root,NodoFil n){

    if(root == NULL) return 0;
    if(strcmp(n.cliente,root->n.cliente) < 0) return searchFi(root->left,n);
    else if(strcmp(n.cliente,root->n.cliente) > 0) return searchFi(root->right,n);
    else return 1;
}

// ------------------------------------------------------------------------------------------------

NodoFil getNodoFil(Filial f){
    return f->n;
}

Filial getLeftFil(Filial f){
    if(f == NULL) return NULL;
    return f->left;
}
Filial getRightFil(Filial f){
    if(f == NULL) return NULL;
    return f->right;
}

InfoFil getInfoFil(Filial f){
    return f->n.i;
}
InfoFil getInfoNextFil(InfoFil i){
    if(i == NULL) return NULL;
    return i->next;
}

float getPrecoFil(InfoFil i){
    return i->preco;
}
int getQuantFil(InfoFil i){
    return i->quant;
}
int getMesFil(InfoFil i){
    return i->mes;
}
char getPromoFil(InfoFil i){
    return i->promo;
}

Filial inicializa_Filial(){
    Filial f = (Filial) malloc(sizeof(struct avlFilial));
    f = NULL;
    return f;
}

char** tokenizeLinhaNodeDyn(char* vendaRaw) {
    int index = 0;
    char** campos = (char**) malloc(7 * sizeof(char*));
    char* temp = strdup(vendaRaw);
    char* token = strtok(temp," ");
    while(token != NULL){
        campos[index] = strdup(token);
        token = strtok(NULL," ");
        index++;
    }
    return campos;
}

NodoFil mkNodeVenda(char* linhaVenda){

    char** campos;
    NodoFil f;
    campos = tokenizeLinhaNodeDyn(linhaVenda);

    InfoFil i = malloc(sizeof(struct infofil)); 
    
    i->next = NULL;
    i->preco = atof(campos[1]);
    i->quant = atoi(campos[2]);
    i->promo = *campos[3];
    i->produto = strdup(campos[0]);
    i->mes = atoi(campos[5]);

    f.cliente = strdup(campos[4]);
    f.i = i;
    return f; 
}

NodoFil editNodoFi(char* c){

    NodoFil f;
    f.cliente = strdup(c);
    InfoFil i = malloc(sizeof(struct infofil)); 
    i = NULL;
    f.i = i;
    return f;
}
