#include "funcoes.h"

// ------------------------------------ Funções úteis globais -------------------------------------

/*
 * Procura uma string numa lista de strings.
 */
int elem(char** lista, char* key){

    int found = 0;
    
    for(int i = 0; lista[i] != NULL && found == 0; i++){
        if(!strcmp(lista[i],key)) found = 1;
    }
    return found;
}

/*
 * Parte uma string aos bocados e coloca cada bocado numa posição do array.
 */
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

/*
 * Conta quanto caracteres "x" existe numa string.
 */
int contaChar(char* iniciais, char x){

    int count = 0;
    for(int i = 0; iniciais[i]; i++)
        if(iniciais[i] == x) count++;

    return count;
}

// ----------------------------------- Funções da struct venda ------------------------------------

/*
 * Adiciona uma venda a uma estrutura de dados.
 */
void addVenda(Vendas* v, char* tokensArray[7], int index){

    v[index].produto = strdup(tokensArray[0]);
    v[index].preco = atof(tokensArray[1]);
    v[index].quant = atoi(tokensArray[2]);
    v[index].promo = *tokensArray[3];
    v[index].cliente = strdup(tokensArray[4]);
    v[index].mes = atoi(tokensArray[5]);
    v[index].filial = atoi(tokensArray[6]);
}

/*
 * Conta quantas vendas foram feitas por um cliente.
 */
int contaVendas(Vendas* v, char* cliente){

    int count = 0;

    for(int i = 0;v[i].produto; i++)
        if(!strcmp(v[i].cliente,cliente)) count++;

    return count;
}

/*
 * Conta quantas quantas vendas foram feitas numa filial.
 */
int contaFilial(Vendas* v, int filial){

    int count = 0;
    for(int i = 0; v[i].produto; i++)
        if(v[i].filial == filial) count++;

    return count;
}
/*
 * Calcula faturação total registada.
 */
float contaFaturacao(Vendas*v){

    float r = 0;
    for(int i = 0; v[i].produto; i++)
        r += v[i].preco * v[i].quant;
    return r;
}
// --------------------------- Parte de validação (apenas de uma linha) ---------------------------

/*
 * Valida um cliente de acordo com a sua estrutura.
 */
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
/*
 * Valida um produto de acordo com a sua estrutura.
 */
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
/*
 * Valida uma venda.
 * Função de procura (elem) muito pouco eficiente.
 */
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

// --------------------------------- Parte de guardar nas listas ----------------------------------

/*
 * Lê do ficheiro clientes e passa cada linha para um array de strings.
 * Passa para um array o elemento da primeira posição da linha lida, ou seja, a letra para ser contada.
 * Retorna o número de clientes válidos inseridos.
 */
int guardaClientes(FILE *fp, char** lista){

    char str[MAXBUFCLIENT];
    char* linha;
    char* iniciais = malloc(sizeof(char*));

    int index = 0;
    while(fgets(str,MAXBUFCLIENT,fp)){
        linha = strtok(str,"\n\r");
        iniciais[index] = linha[0];
        if(validaCliente(linha)){
            lista[index] = strdup(linha);
            index++;
        }
    }
    printf("Foram encontrados %d J's nos clientes\n",contaChar(iniciais,'J'));
    return index;
}
/*
 * Lê do ficheiro produtos e passa cada linha para um array de strings.
 * Retorna o número de produtos válidos inseridos.
 */
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
/*
 * Lê do ficheiro vendas.
 * Passa todas as linhas para uma struct de vendas "vTodas".
 * Passa apenas as linhas válidas para uma struct de vendas "vBoas".
 * Passa apenas as linhas válidas para o array de string "listaVendas".
 * Escreve num ficheiro de texto apenas as vendas válidas.
 * Retorna o número de vendas válidas.
 */
int guardaVendas(FILE *fp, char** listaVendas, char** listaProdutos, char** listaClientes, Vendas* vTodas, Vendas* vBoas, FILE* vValidasFicheiro){

    char str[MAXBUFVENDAS];
    char* linha;
    int index = 0;
    char* tokensArray[7];
    int fail = 0; // conta quantas linhas inválidas foram lidas

    while(fgets(str,MAXBUFVENDAS,fp)){
        linha = strtok(str,"\n\r");
        linhaToArray(linha,tokensArray);
        if(validaVendas(tokensArray,listaProdutos,listaClientes)){
            listaVendas[index-fail] = strdup(linha); // Guarda em array de strings vendas válidas
            addVenda(vBoas,tokensArray,index-fail); // Guarda em array de struct vendas válidas.
            fprintf(vValidasFicheiro,"%s\n",listaVendas[index-fail]); // Escreve no ficheiro vendas válidas.
        }
        else fail++;
        addVenda(vTodas,tokensArray,index); // Guarda em array de struct todas as vendas
        index++;
    }
    return index-fail;
}