typedef struct venda{
    char *produto;
    float preço;
    int quant;
    char promo_norm;
    char *cliente;
    int mes;
    int filial;
}*Venda;

#define MAXBUFPRODCLIENT 10
#define MAXPRODS 200000
#define MAXCLIENT 20000
#define MAXVENDAS 1000000
#define MAXBUFVENDAS 100

// API

char* getLine(char** lista, char *str, int line);
int elem(char** lista, char* key, int lines);
int validaClienteProduto(char* linha);
//int validaRep(int l, int c, char lista[l][c], int *rep);
int guardaProdutosClientes(FILE *fp, char** lista);