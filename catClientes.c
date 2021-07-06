#include "AVL.h"
#include "CatClientes.h"

struct cat_clientes{
    AVL array[26];
};

struct lst_clientes{
    char** lista;
};

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
    catc->array[a] = insert(catc->array[a],linha);
    return catc;
}

int existeCliente(Cat_Clientes catc, Cliente c){
    return search(catc->array[getIndexC(c)],getCodCliente(c));
}

char** getListaClientes(Lista_Clientes lc){
    return lc->lista;
}

void printCatCliente(Cat_Clientes cp){
    for(int i = 0; i < 26; i++)
        preOrder(cp->array[i]);
}

/* ------------------------------------------- Lista ------------------------------------------- */

Lista_Clientes inOrderCLista(AVL root, Lista_Clientes lc, int* index){
    if(root != NULL){ 
        inOrderCLista(getLeft(root),lc,index);
        lc->lista[*index] = strdup(getCode(root));
        *index = *index + 1;
        inOrderCLista(getRight(root),lc,index); 
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
    lc = inOrderCLista(catc->array[posicao],lc,&inx);
    return lc;
}

Lista_Clientes catcToLista(Cat_Clientes catc){
    Lista_Clientes lc = initListaClientes();
    int inx = 0;

    for(int i = 0; i < 26; i++){
        lc = inOrderCLista(catc->array[i],lc,&inx);
    }
    return lc;
}

void printListaClientes(Lista_Clientes lc){
    for(int i = 0; lc->lista[i]; i++)
        printf("%s\n",lc->lista[i]);
}

/* ------------------------------------------------------------------------------------------------*/

void guardaClientes(FILE *fp,Cat_Clientes catc, int* cLidos, int* cTotal){

    char str[7];
    char* linha;

    while(fgets(str,7,fp)){
        linha = strtok(str,"\n\r");
        Cliente c = criaCliente(linha);
        if(validaCliente(c)){
            catc = insereCliente(catc,c);
            *cLidos = *cLidos + 1;
        }
        *cTotal = *cTotal + 1;
    }
}