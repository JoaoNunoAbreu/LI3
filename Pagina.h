#include "CatProds.h"
#include "CatClientes.h"

typedef struct list_strings* List_Strings;
typedef struct pag *Pagina;

// ------------- List_Strings -------------

List_Strings initListaStrings();
List_Strings criaLsLp(Lista_Prods lp);
List_Strings criaLsLc(Lista_Clientes lc);
List_Strings addLinha(List_Strings ls, char* linha,int index);
int sizeList_Strings(List_Strings ls);
void printList_Strings(List_Strings ls);
void printNList(List_Strings ls, int k);

// ---------------- Página ----------------

char* getLine(List_Strings ls,int i);
List_Strings getPorcao(Pagina p);
Pagina initPag(List_Strings ls);
Pagina getPagSeguinte(List_Strings ls);
void printPag(Pagina p);
// -------------- Navegador ---------------
void navegador(List_Strings ls);