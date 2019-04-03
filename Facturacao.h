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
int getNumFilial(Info i);
char getPromo(Info i);
void setProduto(Nodo n, char* produto);

Nodo mkNodoVenda(char* linhaVenda);

Facturacao inicializa_Facturacao();
Facturacao insertF(Facturacao node, Nodo n);
Facturacao searchF(Facturacao root,char* produto);
void preOrderF(Facturacao root);