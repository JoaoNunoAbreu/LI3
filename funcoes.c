#include "funcoes.h"

/*-----------------------------------------------------------------------------------------------*/

int heightPC(AVLPC a){ 
    if(a == NULL) return 0; 
    return a -> height; 
}

int max(int a, int b){ 
    return (a > b)? a : b; 
}

AVLPC newNode(char* code){

    AVLPC a = (AVLPC) malloc(sizeof(struct avlPC));
    a -> code = strdup(code);
    a -> left = NULL; 
    a -> right = NULL; 
    a -> height = 1;
    return a;
}

AVLPC rightRotate(AVLPC y){ 
    
    AVLPC x = y -> left; 
    AVLPC T2 = x -> right; 
    x->right = y; 
    y->left = T2; 
    y->height = max(heightPC(y->left), heightPC(y->right))+1; 
    x->height = max(heightPC(x->left), heightPC(x->right))+1; 
    return x; 
}

AVLPC leftRotate(AVLPC x){ 

    AVLPC y = x -> right; 
    AVLPC T2 = y -> left; 
    y -> left = x; 
    x -> right = T2; 
    x -> height = max(heightPC(x->left), heightPC(x->right))+1; 
    y -> height = max(heightPC(y->left), heightPC(y->right))+1; 
    return y; 
} 

int getBalance(AVLPC N){ 
    if (N == NULL) return 0; 
    return heightPC(N->left) - heightPC(N->right); 
} 

AVLPC insert(AVLPC node, char* code) { 

    if (node == NULL) return(newNode(code)); 
  
    if (strcmp(code,node->code) < 0) node -> left  = insert(node->left,code); 
    else if (strcmp(code,node -> code) > 0) node->right = insert(node->right,code); 
    else return node; 
  
    node -> height = 1 + max(heightPC(node->left),heightPC(node->right)); 

    int balance = getBalance(node); 
  
    /* Left Left Case */
    if (balance > 1 && strcmp(code,node->left->code) < 0) return rightRotate(node); 
  
    /* Right Right Case */
    if (balance < -1 && strcmp(code,node->right->code) > 0) return leftRotate(node); 
  
    /* Left Right Case */
    if (balance > 1 && strcmp(code,node->left->code) > 0){ 
        node->left = leftRotate(node->left); 
        return rightRotate(node); 
    } 
    /* Right Left Case */
    if (balance < -1 && strcmp(code,node->right->code) < 0){ 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 
    return node; 
}

void preOrder(AVLPC root){ 
    if(root != NULL){ 
        printf("%s\n",root->code); 
        preOrder(root->left); 
        preOrder(root->right); 
    } 
}

int search(AVLPC root,char* key){

    if(root == NULL) return 0;
    if(strcmp(key,root->code) < 0) return search(root->left,key);
    else if(strcmp(key,root->code) > 0) return search(root->right,key);
    else return 1;
}

/*-----------------------------------------------------------------------------------------------*/

char** tokenizeLinhaVendaDyn(char* vendaRaw) {
    int index = 0;
    char** campos = (char**) malloc(7 * sizeof(char*)); /* 7 pois a struct vendas tem 7 parâmetros.*/
    char* temp = strdup(vendaRaw);
    char* token = strtok(temp," ");
    while(token != NULL){
        campos[index] = strdup(token);
        token = strtok(NULL," ");
        index++;
    }
    return campos;
}

int contaChar(Vendas* v, char x){

    int count = 0;
    for(int i = 0; v[i].cliente; i++)
        if(v[i].cliente[0] == x) count++;

    return count;
}

void addVenda(Vendas* v, char** tokensArray, int index){

    v[index].produto = strdup(tokensArray[0]);
    v[index].preco = atof(tokensArray[1]);
    v[index].quant = atoi(tokensArray[2]);
    v[index].promo = tokensArray[3];
    v[index].cliente = strdup(tokensArray[4]);
    v[index].mes = atoi(tokensArray[5]);
    v[index].filial = atoi(tokensArray[6]);
}

Vendas mkVenda(char* linhaVenda){

    char** campos;
    Vendas vendaAux;
    campos = tokenizeLinhaVendaDyn(linhaVenda);

    vendaAux.produto = strdup(campos[0]);
    vendaAux.preco = atof(campos[1]);
    vendaAux.quant = atoi(campos[2]);
    vendaAux.promo = campos[3];
    vendaAux.cliente = strdup(campos[4]);
    vendaAux.mes = atoi(campos[5]);
    vendaAux.filial = atoi(campos[6]);

    return vendaAux;   
}

int contaMaiorLinha(char** lista){

    int max = 0;

    for(int i = 0; lista[i]; i++)
        if(strlen(lista[i]) > max) max = strlen(lista[i]);

    return max;
}

int contaVendas(Vendas* v, char* cliente){

    int count = 0;

    for(int i = 0;v[i].produto; i++)
        if(!strcmp(v[i].cliente,cliente)) count++;

    return count;
}

int contaFilial(Vendas* v, int filial){

    int count = 0;
    for(int i = 0; v[i].produto; i++)
        if(v[i].filial == filial) count++;

    return count;
}

float contaFaturacao(Vendas*v){

    float r = 0;
    for(int i = 0; v[i].produto; i++)
        r += v[i].preco * v[i].quant;
    return r;
}

int contaPrecos(Vendas* v, int x){

    int count = 0;
    for(int i = 0; v[i].produto; i++)
        if(v[i].preco == x) count++;
    return count;
}

int contaProdutosEnvolvidos(Vendas* v){
    
    int count = 0;
    AVLPC envolvidosP = NULL;
    for(int j = 0; v[j].produto ; j++){
        if(!search(envolvidosP,v[j].produto)){
            envolvidosP = insert(envolvidosP,strdup(v[j].produto));
            count++;
        }
    }

    return count;
}

int contaClientesEnvolvidos(Vendas* v){

    int count = 0;
    AVLPC envolvidosC = NULL;
    for(int j = 0; v[j].cliente; j++){
        if(!search(envolvidosC,v[j].cliente)){
            envolvidosC = insert(envolvidosC,strdup(v[j].cliente));
            count++;
        }
    }
    return count;
}

int contaUnidades(Vendas* v){

    int sum = 0;
    for(int i = 0; v[i].produto; i++)
        sum += v[i].quant;
    return sum;
}

/*-----------------------------------------------------------------------------------------------*/

int validaCliente(char* linha){

    int r = 1;
    if(linha == NULL || strlen(linha) != 5) return 0;
    
    if(!isupper(linha[0])) r = 0;
    else {
        int num = atoi(linha+1);
        if(num < 1000 || num > 5000) r = 0;
    }

    return r;
}

int validaVendas(char* linhaVenda, AVLPC rootP, AVLPC rootC){

    int r = 1;
    char** tokensArray = tokenizeLinhaVendaDyn(linhaVenda);

    if(atof(tokensArray[1]) < 0 || atof(tokensArray[1]) > 999.99) r = 0;
    if(r == 1 && (atoi(tokensArray[2]) < 0 || atoi(tokensArray[2]) > 200)) r = 0;
    if(r == 1 && (*tokensArray[3] != 'N'   && *tokensArray[3] != 'P')) r = 0;
    if(r == 1 && (atoi(tokensArray[5]) < 0 || atoi(tokensArray[5]) > 12)) r = 0;
    if(r == 1 && (atoi(tokensArray[6]) < 0 || atoi(tokensArray[6]) > 3)) r = 0;
    if(r == 1 && (!search(rootC,tokensArray[4]))) {
        r = 0;
        indexCI++;
        clientesInvalidos[indexCI] = strdup(tokensArray[4]); /* Guarda em array a lista de clientes inválidos*/
    }
    if(!search(rootP,tokensArray[0])) {
        r = 0;
        produtosInvalidos[indexPI] = strdup(tokensArray[0]); /* Guarda em array a lista de produtos inválidos*/
        indexPI++;
    }

    return r;
}

int guardaClientes(FILE *fp,AVLPC* root){

    char str[MAXBUFCLIENT];
    char* linha;

    int index = 0;
    while(fgets(str,MAXBUFCLIENT,fp)){
        linha = strtok(str,"\n\r");
        if(validaCliente(linha)){
            *root = insert(*root,strdup(linha));
            index++;
        }
    }
    return index;
}

int guardaVendas(FILE *fp, char** listaVendas, AVLPC rootP, AVLPC rootC, Vendas* vTodas, Vendas* vBoas){

    FILE *vValidasFicheiro = fopen("Vendas_1MValidas.txt","w");
    char str[MAXBUFVENDAS];
    char* linha; 
    int index = 0;
    int fail = 0; /* conta quantas linhas inválidas foram lidas*/
    indexCI = indexPI = 0;

    while(fgets(str,MAXBUFVENDAS,fp)){
        linha = strtok(str,"\n\r");
        if(validaVendas(strdup(linha),rootP,rootC)){
            listaVendas[index-fail] = strdup(linha);  /*Guarda em array de strings vendas válidas.*/
            vBoas[index-fail] = mkVenda(strdup(linha));  /*Guarda em array de struct vendas válidas.*/
            fprintf(vValidasFicheiro,"%s\n",listaVendas[index-fail]); /*Escreve no ficheiro vendas válidas.*/
        }
        else fail++;
        vTodas[index] = mkVenda(strdup(linha)); /* Guarda em array de struct todas as vendas*/
        index++;
    }
    return index-fail;
}