#include "funcoes.h"

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
    Cat_Prods envolvidosP = inicializa_CatProds();

    for(int j = 0; v[j].produto ; j++){
        if(!existeProd(envolvidosP,criaProd(v[j].produto))){
            envolvidosP = insereProd(envolvidosP,criaProd(v[j].produto));
            count++;
        }
    }
    return count;
}

int contaClientesEnvolvidos(Vendas* v){

    int count = 0;
    Cat_Clientes envolvidosC = inicializa_CatClientes();
    for(int j = 0; v[j].cliente; j++){
        if(!existeCliente(envolvidosC,criaCliente(v[j].cliente))){
            envolvidosC = insereCliente(envolvidosC,criaCliente(v[j].cliente));
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

int validaVendas(char* linhaVenda, Cat_Prods catp, Cat_Clientes catc){

    int r = 1;
    char** tokensArray = tokenizeLinhaVendaDyn(linhaVenda);

    if(atof(tokensArray[1]) < 0 || atof(tokensArray[1]) > 999.99) r = 0;
    if(r == 1 && (atoi(tokensArray[2]) < 0 || atoi(tokensArray[2]) > 200)) r = 0;
    if(r == 1 && (*tokensArray[3] != 'N'   && *tokensArray[3] != 'P')) r = 0;
    if(r == 1 && (atoi(tokensArray[5]) < 0 || atoi(tokensArray[5]) > 12)) r = 0;
    if(r == 1 && (atoi(tokensArray[6]) < 0 || atoi(tokensArray[6]) > 3)) r = 0;
    if(r == 1 && (!existeCliente(catc,criaCliente(tokensArray[4])))) {
        r = 0;
        indexCI++;
        /*clientesInvalidos[indexCI] = strdup(tokensArray[4]);  Guarda em array a lista de clientes inválidos*/
    }
    if(!existeProd(catp,criaProd(tokensArray[0]))) {
        r = 0;
        /*produtosInvalidos[indexPI] = strdup(tokensArray[0]);  Guarda em array a lista de produtos inválidos*/
        indexPI++;
    }

    return r;
}

int guardaVendas(FILE *fp, char** listaVendas, Cat_Prods catp, Cat_Clientes catc, Vendas* vTodas, Vendas* vBoas){

    FILE *vValidasFicheiro = fopen("Vendas_1MValidas.txt","w");
    char str[MAXBUFVENDAS];
    char* linha; 
    int index = 0;
    int fail = 0; /* conta quantas linhas inválidas foram lidas*/
    indexCI = indexPI = 0;

    while(fgets(str,MAXBUFVENDAS,fp)){
        linha = strtok(str,"\n\r");
        if(validaVendas(strdup(linha),catp,catc)){
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