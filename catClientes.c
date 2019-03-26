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

/*----------------------------------------- Catálogo --------------------------------------------*/

int getIndexC(Cliente c){
    return getChar0C(c) - 65;
}

Cat_Clientes inicializa_CatClientes(){
    Cat_Clientes catc = (Cat_Clientes) malloc(sizeof(struct cat_clientes));
    for(int i = 0; i < 26; i++)
        catc->array[i] = NULL;
    return catc;
}

Cat_Clientes insereCliente(Cat_Clientes catc, Cliente c){

    int a = getIndexC(c);
    char* linha = getCodCliente(c);
    catc->array[a] = insertC(catc->array[a],linha);
    return catc;
}

int existeCliente(Cat_Clientes catc, Cliente c){
    return searchC(catc->array[getIndexC(c)],getCodCliente(c));
}

void printCatCliente(Cat_Clientes cp){
    for(int i = 0; i < 26; i++)
        preOrderC(cp->array[i]);
}

/* ------------------------------------------- Lista ------------------------------------------- */

Lista_Clientes preOrderCLista(AVLC root, Lista_Clientes lc, int* index){
    if(root != NULL){ 
        lc->lista[*index] = strdup(root->code);
        *index = *index + 1;
        preOrderCLista(root->left,lc,index);
        preOrderCLista(root->right,lc,index); 
    }
    return lc;
}

Lista_Clientes initListaClientes(){
    Lista_Clientes lc = (Lista_Clientes) malloc(sizeof(struct lst_clientes));
    char** campos = (char**) malloc(20000 * sizeof(char*));
    lc->lista = campos;
    return lc;
}

Lista_Clientes listaPorLetraC(Cat_Clientes catc, char letra){
    int posicao = letra - 65;
    Lista_Clientes lc = initListaClientes();
    int inx = 0;
    lc = preOrderCLista(catc->array[posicao],lc,&inx);
    return lc;
}

int sizeOfLista_Clientes(Lista_Clientes lc){
    int count;
    for(count = 0; lc->lista[count]; count++);
    return count;
}

void printListaClientes(Lista_Clientes lc){
    for(int i = 0; lc->lista[i]; i++)
        printf("%s\n",lc->lista[i]);
}

/* ------------------------------------------------------------------------------------------------*/

int guardaClientes(FILE *fp,Cat_Clientes catc){

    char str[7];
    char* linha;

    int index = 0;
    while(fgets(str,7,fp)){
        linha = strtok(str,"\n\r");
        Cliente c = criaCliente(linha);
        if(validaCliente(c)){
            catc = insereCliente(catc,c);
            index++;
        }
    }
    return index;
}