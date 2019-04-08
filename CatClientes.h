#include "Cliente.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
		
typedef struct cat_clientes* Cat_Clientes;
typedef struct lst_clientes* Lista_Clientes; 
		
Cat_Clientes inicializa_CatClientes();
Cat_Clientes insereCliente(Cat_Clientes catc, Cliente c);
int existeCliente(Cat_Clientes catc, Cliente c);
void printCatCliente(Cat_Clientes cp);
 
Lista_Clientes initListaClientes();
Lista_Clientes listaPorLetraC(Cat_Clientes catc, char letra);
Lista_Clientes catcToLista(Cat_Clientes catc);
char** getListaClientes(Lista_Clientes lc);
void printListaClientes(Lista_Clientes lc);

void guardaClientes(FILE *fp,Cat_Clientes catc, int* cLidos, int* cTotal);