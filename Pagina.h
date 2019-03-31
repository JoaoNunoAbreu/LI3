#include "CatProds.h"
#include "CatClientes.h"

typedef struct list_strings* List_Strings;
typedef struct pag *Pagina;

// ------------- List_Strings -------------

List_Strings criaLsLp(Lista_Prods lp);
List_Strings criaLsLc(Lista_Clientes lc);
int sizeList_Strings(List_Strings ls);
void printList_Strings(List_Strings ls);

// ---------------- Página ----------------

char* getLine(List_Strings ls,int i);
List_Strings getPorcao(Pagina p);
Pagina getPagSeguinte(List_Strings ls);
void printPag(Pagina p);