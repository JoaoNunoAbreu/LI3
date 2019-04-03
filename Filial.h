// Apontador para lista de clientes e respectivas quantidades
typedef struct infofil* InfoFil;

// Nodo de AVL de um filial
typedef struct nodeFil{
    char* cliente;
    InfoFil i;
}NodoFil;

typedef struct avlFilial* Filial;

NodoFil getNodoFil(Filial f);
Filial getLeftFil(Filial f);
Filial getRightFil(Filial f);
InfoFil getInfoFil(Filial f);
InfoFil getInfoNextFil(InfoFil i);
float getPrecoFil(InfoFil i);
int getQuantFil(InfoFil i);
int getMesFil(InfoFil i);
char getPromoFil(InfoFil i);


Filial insertFi(Filial node, NodoFil n);
Filial searchFi(Filial root,char* cliente);
void inOrderFi(Filial root);

Filial inicializa_Filial();
NodoFil mkNodeVenda(char* linhaVenda);
NodoFil editNodoFi(char* c);