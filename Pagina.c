#include "Pagina.h"
#include <ctype.h>

struct list_strings{
    char** lista;
};

struct pag{
    List_Strings porcao;
};

// ------------- List_Strings -------------

List_Strings initListaStrings(){
    List_Strings ls = (List_Strings) malloc(sizeof(struct list_strings));
    char** campos = (char**) malloc(5000000 * sizeof(char*));
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

List_Strings addLinha(List_Strings ls, char* linha,int index){
    ls->lista[index] = strdup(linha);
    return ls;
}

int sizeList_Strings(List_Strings ls){
    int i;
    for(i = 0; ls->lista[i] != NULL ; i++);
    return i;
}

void printList_Strings(List_Strings ls){
    for(int i = 0; ls->lista[i]; i++)
        printf("%s\n",ls->lista[i]);
}

void printNList(List_Strings ls, int k){
    int count = 0;
    while(ls->lista[count] != NULL && count < k){ 
        printf("%s\n",ls->lista[count]);
        count++;
    }
}

// ---------------- Página ----------------

char* getLine(List_Strings ls,int i){
    if(ls == NULL || ls->lista[i] == NULL) return NULL;
    char* temp = strdup(ls->lista[i]);
    char* token = strtok(temp," ");
    token = strtok(NULL," ");
    return token;
}

List_Strings getPorcao(Pagina p){
    return p->porcao;
}

void printPag(Pagina p){
    if(p != NULL){
        int num = sizeList_Strings(p->porcao);
        if(sizeList_Strings(p->porcao) > 10) num = 10;

        if(num == 0) printf("Página vazia\n");
        else{
            printf("--------------- Início de página ----------------\n");
            for(int i = 0; i < num; i++)
                printf("%s\n",p->porcao->lista[i]);
            printf("----------------- Fim de página -----------------\n");
        }
    }
}

Pagina initPag(List_Strings ls){
    Pagina p = (Pagina) malloc(sizeof(struct pag));
    p->porcao = ls;
    return p;
}

Pagina getPagSeguinte(List_Strings ls){
    
    Pagina p = initPag(ls);
    if(sizeList_Strings(ls) > 10) {
        p->porcao->lista = (ls)->lista + 10;
    }
    return p;
}

// ---------------- Navegador ----------------

void navegador(List_Strings ls){

    int page = 0;
    int numPaginas = sizeList_Strings(ls) / 10; 
    Pagina p = NULL;

    while(page >= 0){
        List_Strings tmp = initListaStrings();
        for(int i = 0; ls->lista[i]; i++){
            *(tmp->lista+i) = *(ls->lista+i);
        }
        printf("Que número de página pretende ler? (para parar inserir número negativo)\n");
        scanf(" %d",&page);
        if(page > numPaginas) printf("Número de página demasiado grande\n");
        else if(page >= 0){
            p = initPag(tmp);
            if(page != 0){
                for(int i = 0; i < page ; i++)
                    p = getPagSeguinte(tmp);
            }
            printPag(p);
        }
    }
}