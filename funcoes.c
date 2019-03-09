#include "funcoes.h"

int elem(char** lista, char* key){

    int found = 0;
    
    for(int i = 0; lista[i] != NULL && found == 0; i++){
        if(!strcmp(lista[i],key)) found = 1;
    }
    return found;
}

void linhaToArray(char* linha,char* tokensArray[7]){

    char* line = strdup(linha);
    char* token = strtok(line," ");
    int i = 0;
    while(token != NULL) {
        tokensArray[i] = token;    
        token = strtok(NULL," ");
        i++;
    }
}

int contaChar(char* iniciais, char x){

    int count = 0;
    for(int i = 0; iniciais[i]; i++)
        if(iniciais[i] == x) count++;

    return count;
}

void addVenda(Vendas* v, char* tokensArray[7], int index){

    v[index].produto = strdup(tokensArray[0]);
    v[index].preco = atof(tokensArray[1]);
    v[index].quant = atoi(tokensArray[2]);
    v[index].promo = *tokensArray[3];
    v[index].cliente = strdup(tokensArray[4]);
    v[index].mes = atoi(tokensArray[5]);
    v[index].filial = atoi(tokensArray[6]);
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

int contaProdutosEnvolvidos(Vendas* vBoas, int vLidas){

    char* envolvidosP[vLidas];
    int i = 0;

    for(int j = 0; j < vLidas; j++){
        if(!elem(envolvidosP,vBoas[j].produto)) envolvidosP[i++] = strdup(vBoas[j].produto);
    }

    return i;
}

int contaClientesEnvolvidos(Vendas* vBoas, int vLidas){

    char* envolvidosC[vLidas];
    int i = 0;

    for(int j = 0; j < vLidas; j++){
        if(!elem(envolvidosC,vBoas[j].cliente)) envolvidosC[i++] = strdup(vBoas[j].cliente);
    }
    return i;
}

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

int validaProduto(char* linha){

    int r = 1;
    if(linha == NULL || strlen(linha) != 6) return 0;

    if(!isupper(linha[0]) || !isupper(linha[1])) r = 0;
    else{
        int num1 = atoi(linha+2);
        if(num1 < 1000 || num1 > 9999) r = 0;
    }
    return r;
}

int validaVendas(char* tokensArray[7], char** listaProdutos, char** listaClientes){

    int r = 1;

    if(atof(tokensArray[1]) < 0 || atof(tokensArray[1]) > 999.99) r = 0;
    if(r == 1 && (atoi(tokensArray[2]) < 0 || atoi(tokensArray[2]) > 200)) r = 0;
    if(r == 1 && (*tokensArray[3] != 'N'   && *tokensArray[3] != 'P')) r = 0;
    if(r == 1 && (atoi(tokensArray[5]) < 0 || atoi(tokensArray[5]) > 12)) r = 0;
    if(r == 1 && (atoi(tokensArray[6]) < 0 || atoi(tokensArray[6]) > 3)) r = 0;
    if(r == 1 && (!elem(listaClientes,tokensArray[4]))) r = 0;
    if(r == 1 && (!elem(listaProdutos,tokensArray[0]))) r = 0;

    return r;
}

int guardaClientes(FILE *fp, char** lista){

    char str[MAXBUFCLIENT];
    char* linha;
    char* iniciais = malloc(sizeof(char*));

    int index = 0;
    while(fgets(str,MAXBUFCLIENT,fp)){
        linha = strtok(str,"\n\r");
        if(validaCliente(linha)){
            iniciais[index] = linha[0];
            lista[index] = strdup(linha);
            index++;
        }
    }
    /*printf("Foram encontrados %d J's nos clientes\n",contaChar(iniciais,'J'));*/
    return index;
}

int guardaProdutos(FILE *fp, char** lista){

    char str[MAXBUFPROD];
    char* linha;

    int index = 0;
    while(fgets(str,MAXBUFPROD,fp)){
        linha = strtok(str,"\n\r");
        if(validaProduto(linha)){
            lista[index] = strdup(linha);
            index++;
        }
    }
    return index;
}

int guardaVendas(FILE *fp, char** listaVendas, char** listaProdutos, char** listaClientes, Vendas* vTodas, Vendas* vBoas){

    FILE *vValidasFicheiro = fopen("Vendas_1MValidas.txt","w");
    char str[MAXBUFVENDAS];
    char* linha;
    int index = 0;
    char* tokensArray[7];
    int fail = 0; /* conta quantas linhas inválidas foram lidas*/

    while(fgets(str,MAXBUFVENDAS,fp)){
        linha = strtok(str,"\n\r");
        linhaToArray(linha,tokensArray);
        if(validaVendas(tokensArray,listaProdutos,listaClientes)){
            listaVendas[index-fail] = strdup(linha); /* Guarda em array de strings vendas válidas*/
            addVenda(vBoas,tokensArray,index-fail); /* Guarda em array de struct vendas válidas.*/
            fprintf(vValidasFicheiro,"%s\n",listaVendas[index-fail]); /* Escreve no ficheiro vendas válidas.*/
        }
        else fail++;
        addVenda(vTodas,tokensArray,index); /* Guarda em array de struct todas as vendas*/
        index++;
    }
    return index-fail;
}