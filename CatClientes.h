#include "Cliente.h"
		
typedef struct cat_clientes* Cat_Clientes;
typedef struct lst_clientes* Lista_Clientes; 
		
Cat_Clientes inicializa_CatClientes();
Cat_Clientes insereCliente(Cat_Clientes catc, Cliente c);
int existeCliente(Cat_Clientes catc, Cliente c);
void printCatCliente(Cat_Clientes cp);
 
Lista_Clientes initListaClientes();
Lista_Clientes listaPorLetraC(Cat_Clientes catc, char letra);
int sizeOfLista_Clientes(Lista_Clientes lc);
void printListaClientes(Lista_Clientes lc);

/**
 * Lê do ficheiro clientes e passa cada linha para o catálogo de clientes.
 * Retorna o número de clientes válidos inseridos.
 */
int guardaClientes(FILE *fp,Cat_Clientes catc);