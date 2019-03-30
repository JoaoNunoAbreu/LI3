#include "Facturacao.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct info{
    float preco;
    int quant;
    char promo;
    int mes;
    int filial;
    struct info *next;
};

struct avlf{
    Nodo n;
    struct avlf *left,*right;
    int height;
};

// ------------------------------------------------------------------------------------------------

int heightF(Facturacao a){ 
    if(a == NULL) return 0; 
    return a -> height; 
}
int maxF(int a, int b){ 
    return (a > b)? a : b; 
}
Facturacao newNodeF(Nodo n){

    Facturacao a = (Facturacao) malloc(sizeof(struct avlf));
    a -> n = n; // ---------------------------- PROVAVEL ERRO AQUI ----------------------------
    a -> left = NULL; 
    a -> right = NULL; 
    a -> height = 1;
    return a;
}
Facturacao rightRotateF(Facturacao y){ 
    
    Facturacao x = y -> left; 
    Facturacao T2 = x -> right; 
    x->right = y; 
    y->left = T2; 
    y->height = maxF(heightF(y->left), heightF(y->right))+1; 
    x->height = maxF(heightF(x->left), heightF(x->right))+1; 
    return x; 
}
Facturacao leftRotateF(Facturacao x){ 

    Facturacao y = x -> right; 
    Facturacao T2 = y -> left; 
    y -> left = x; 
    x -> right = T2; 
    x -> height = maxF(heightF(x->left), heightF(x->right))+1; 
    y -> height = maxF(heightF(y->left), heightF(y->right))+1; 
    return y; 
} 
int getBalanceF(Facturacao N){ 
    if (N == NULL) return 0; 
    return heightF(N->left) - heightF(N->right); 
} 

Facturacao insertF(Facturacao node, Nodo n){ 

    if (node == NULL) return(newNodeF(n));

    if (strcmp(n.produto,node->n.produto) < 0) node -> left  = insertF(node->left,n); 
    else if (strcmp(n.produto,node -> n.produto) > 0) node->right = insertF(node->right,n); 
    else {
        node->n.i->next = n.i;
        return node; 
    }
  
    node -> height = 1 + maxF(heightF(node->left),heightF(node->right)); 

    int balance = getBalanceF(node);
  
    // Left Left Case 
    if (balance > 1 && strcmp(n.produto,node->left->n.produto) < 0) return rightRotateF(node); 
  
    // Right Right Case
    if (balance < -1 && strcmp(n.produto,node->right->n.produto) > 0) return leftRotateF(node); 
  
    // Left Right Case
    if (balance > 1 && strcmp(n.produto,node->left->n.produto) > 0){ 
        node->left = leftRotateF(node->left); 
        return rightRotateF(node); 
    } 
    // Right Left Case
    if (balance < -1 && strcmp(n.produto,node->right->n.produto) < 0){ 
        node->right = rightRotateF(node->right); 
        return leftRotateF(node); 
    } 
    return node; 
}
void preOrderF(Facturacao root){ 
    if(root != NULL){ 
        printf("%s\n",root->n.produto); 
        preOrderF(root->left); 
        preOrderF(root->right); 
    } 
}
Facturacao searchF(Facturacao root,Nodo n){

    if(root == NULL) return NULL;
    if(strcmp(n.produto,root->n.produto) < 0) return searchF(root->left,n);
    else if(strcmp(n.produto,root->n.produto) > 0) return searchF(root->right,n);
    else return root;
}

// ------------------------------------------------------------------------------------------------

Nodo getNodo(Facturacao f){
    return f->n;
}

Facturacao getLeftF(Facturacao f){
    if(f == NULL) return NULL;
    return f->left;
}
Facturacao getRightF(Facturacao f){
    if(f == NULL) return NULL;
    return f->right;
}

Info getInfo(Facturacao f){
    return f->n.i;
}
Info getInfoNext(Info i){
    if(i == NULL) return NULL;
    return i->next;
}

float getPreco(Info i){
    return i->preco;
}
int getQuant(Info i){
    return i->quant;
}
int getMes(Info i){
    return i->mes;
}
int getFilial(Info i){
    return i->filial;
}
char getPromo(Info i){
    return i->promo;
}

char** tokenizeLinhaNodoDyn(char* vendaRaw) {
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

Nodo mkNodoVenda(char* linhaVenda){

    char** campos;
    Nodo f;
    campos = tokenizeLinhaNodoDyn(linhaVenda);

    Info i = malloc(sizeof(struct info)); 
    i->preco = atof(campos[1]);
    i->quant = atoi(campos[2]);
    i->promo = *campos[3];
    i->mes = atoi(campos[5]);
    i->filial = atoi(campos[6]);
    i->next = NULL;

    f.produto = strdup(campos[0]);
    f.i = i;
    return f; 
}

Nodo editNodo(int mes, char* p){

    Nodo f;
    f.produto = strdup(p);
    Info i = malloc(sizeof(struct info)); 
    i->mes = mes;
    f.i = i;
    return f;
}

Facturacao inicializa_Facturacao(){ // ---------------------------- Provável erro aqui ---------------
    Facturacao a = (Facturacao) malloc(sizeof(struct avlf));
    a = NULL;
    return a;
}