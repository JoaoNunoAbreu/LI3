#include "Pagina.h"

struct list_strings{
    char** lista;
};

struct pag{
    List_Strings porcao;
};

// ------------- List_Strings -------------

List_Strings initListaStrings(){
    List_Strings ls = (List_Strings) malloc(sizeof(struct list_strings));
    char** campos = (char**) malloc(1000000 * sizeof(char*));
    ls->lista = campos;
    return ls;
}

List_Strings criaLsLp(Lista_Prods lp){
    List_Strings ls = initListaStrings();
    ls->lista = getListaProds(lp);
    return ls;
}

List_Strings criaLsLc(Lista_Clientes lc){
    List_Strings ls = initListaStrings();
    ls->lista = getListaClientes(lc);
    return ls;
}

int sizeList_Strings(List_Strings ls){
    int i;
    for(i = 0; ls->lista[i]; i++);
    return i;
}

void printList_Strings(List_Strings ls){
    for(int i = 0; ls->lista[i]; i++)
        printf("%s\n",ls->lista[i]);
}

// ---------------- Página ----------------

char* getLine(List_Strings ls,int i){
    return ls->lista[i];
}

List_Strings getPorcao(Pagina p){
    return p->porcao;
}

Pagina getPagSeguinte(List_Strings ls){
    Pagina p = (Pagina) malloc(sizeof(struct pag));
    p->porcao = ls;
    if(sizeList_Strings(ls) > 10){
        p->porcao->lista = p->porcao->lista + 10;
    }
    else p->porcao->lista = p->porcao->lista + sizeList_Strings(ls);
    return p;
}

void printPag(Pagina p){
    for(int i = 0; i < 10; i++)
        printf("%s\n",p->porcao->lista[i]);
    printf("------------------------------------\n");
}