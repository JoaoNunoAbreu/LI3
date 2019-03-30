typedef struct info* Info;
typedef struct node{
    char* produto;
    Info i;
}Nodo;

typedef struct avlf *Facturacao;

Nodo getNodo(Facturacao f);
Facturacao getLeftF(Facturacao f);
Facturacao getRightF(Facturacao f);
Info getInfo(Facturacao f);
Info getInfoNext(Info i);
float getPreco(Info i);
int getQuant(Info i);
int getMes(Info i);
int getFilial(Info i);
char getPromo(Info i);

Nodo mkNodoVenda(char* linhaVenda);
Nodo editNodo(int mes, char* p);

Facturacao inicializa_Facturacao();
Facturacao insertF(Facturacao node, Nodo n);
Facturacao searchF(Facturacao root,Nodo n);
void preOrderF(Facturacao root);