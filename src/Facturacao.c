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
    a -> n = n;
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
        Info *temp = &node->n.i;
        while(*temp) temp = &(*temp)->next;
        *temp = n.i;
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
Facturacao searchF(Facturacao root,char* produto){

    if(root == NULL) return NULL;
    if(strcmp(produto,root->n.produto) < 0) return searchF(root->left,produto);
    else if(strcmp(produto,root->n.produto) > 0) return searchF(root->right,produto);
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
    if(f == NULL) return NULL;
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
int getNumFilial(Info i){
    return i->filial;
}
char getPromo(Info i){
    return i->promo;
}

int procuraFilialNaInfo(Info i, int filial){
    int found = 0;
    while(i && !found){
        if(i->filial == filial) found = 1;
        i = i->next;
    }
    return found;
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

Facturacao inicializa_Facturacao(){
    Facturacao a = (Facturacao) malloc(sizeof(struct avlf));
    a = NULL;
    return a;
}

// ------------------------------------------------------------------------------------------------

void updateVendFat(Info i,int mes1, int mes2, int* totalVendas, float* totalFaturado){
    Info* temp = &i;
    while(*temp){
        if((*temp)->mes >= mes1 && (*temp)->mes <= mes2){
            *totalVendas = *totalVendas + 1;
            *totalFaturado += (*temp)->quant * (*temp)->preco;
        }
        temp =&((*temp)->next);
    }
}

void query8Aux(Facturacao f, int mes1, int mes2, int* totalVendas, float* totalFaturado){
    if(f != NULL){ 
        query8Aux(f->left,mes1,mes2,totalVendas,totalFaturado); 
        updateVendFat(getInfo(f),mes1,mes2,totalVendas,totalFaturado);
        query8Aux(f->right,mes1,mes2,totalVendas,totalFaturado);
    } 
}

// -----------------

void updateLligada(Facturacao f, Lligada* a, int filial){
    Info info = f->n.i;
    while(info != NULL){
        if(info->filial == filial){
            push(a,info->quant,f->n.produto);
        }
        info = info -> next;
    }
}

void query11Aux(Facturacao f,Lligada* a, int filial){
    if(f != NULL){ 
        query11Aux(f->left,a,filial); 
        updateLligada(f,a,filial);
        query11Aux(f->right,a,filial); 
    }
}