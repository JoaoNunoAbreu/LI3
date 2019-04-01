#include "SGV.h"

// ------------------------------- Warning : por eliminar -------------------------------

#define MAXVENDAS 1000000
#define MAXBUFVENDAS 32

typedef struct venda{
    char *produto;
    float preco;
    int quant;
    char promo;
    char *cliente;
    int mes;
    int filial;
}Vendas;

char* clientesInvalidos[MAXVENDAS]; int indexCI;
char* produtosInvalidos[MAXVENDAS]; int indexPI;

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
    v[index].promo = *tokensArray[3];
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
    vendaAux.promo = *campos[3];
    vendaAux.cliente = strdup(campos[4]);
    vendaAux.mes = atoi(campos[5]);
    vendaAux.filial = atoi(campos[6]);

    return vendaAux;   
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

int guardaVendas(FILE *fp, Cat_Prods catp, Cat_Clientes catc, Vendas* vTodas, Vendas* vBoas,Facturacao* fat){

    FILE *vValidasFicheiro = fopen("Vendas_1MValidas.txt","w");
    char str[MAXBUFVENDAS];
    char* linha; 
    int index = 0;
    int fail = 0; /* conta quantas linhas inválidas foram lidas*/
    indexCI = indexPI = 0;

    while(fgets(str,MAXBUFVENDAS,fp)){
        linha = strtok(str,"\n\r");
        if(validaVendas(linha,catp,catc)){
            /*vBoas[index-fail] = mkVenda(strdup(linha)); Guarda em array de struct vendas válidas.*/
            *fat = insertF(*fat,mkNodoVenda(linha));
            fprintf(vValidasFicheiro,"%s\n",strdup(linha)); /*Escreve no ficheiro vendas válidas.*/
        }
        else fail++;
        vTodas[index] = mkVenda(strdup(linha)); /* Guarda em array de struct todas as vendas*/
        index++;
    }
    return index-fail;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

struct sgv{
    Cat_Prods catp;
    Cat_Clientes catc;
    //Filial filiais[3];
    Facturacao fat;
};

SGV inicializa_SGV(Cat_Prods catp, Cat_Clientes catc, Facturacao fat){ /*Falta Filial filiais[3]*/
    SGV sgv = malloc(sizeof(struct sgv));
    sgv->catc = catc;
    sgv->catp = catp;
    sgv->fat = fat;
    return sgv;
}

void query1(Cat_Prods catp, Cat_Clientes catc, Facturacao fat){
    char readerFile[256];
    char c;
    char* file_name = NULL;

    printf("Pretende inserir nome do ficheiro de Produtos? (s/n)\n");
    scanf(" %c",&c);
    if(c == 's'){
        printf("Nome do ficheiros com Produtos.txt: \n");
        scanf("%s",readerFile);
        file_name = &readerFile[0];
    }
    else file_name = "Produtos.txt";
    FILE *produtoFicheiro = fopen(file_name,"r");
    if(produtoFicheiro == NULL) {printf("Produtos.txt não foi possível ser carregado.\n"); exit (1);}
    else printf("Ficheiro %s lido com sucesso\n",file_name);


    printf("Pretende inserir nome do ficheiro de Clientes? (s/n)\n");
    scanf(" %c",&c);
    if(c == 's'){
        printf("Nome do ficheiros com Clientes.txt: \n");
        scanf("%s",readerFile);
        file_name = &readerFile[0];
    }
    else file_name = "Clientes.txt";
    FILE *clientesFicheiro = fopen(file_name,"r");
    if(clientesFicheiro == NULL) {printf("Clientes.txt não foi possível ser carregado.\n"); exit (1);}
    else printf("Ficheiro %s lido com sucesso\n",file_name);


    printf("Pretende inserir nome do ficheiro de Vendas? (s/n)\n");
    scanf(" %c",&c);
    if(c == 's'){
        printf("Nome do ficheiros com Vendas.txt: \n");
        scanf("%s",readerFile);
        file_name = &readerFile[0];
    }
    else file_name = "FicheirosTeste/testeVendas2.txt";
    FILE *vendasFicheiro = fopen(file_name,"r");
    if(vendasFicheiro == NULL) {printf("Vendas.txt não foi possível ser carregado.\n"); exit (1);}
    else printf("Ficheiro %s lido com sucesso\n",file_name);

    // --------- Catálogos ---------

    int pLidos = guardaProdutos(produtoFicheiro,catp);
    printf("Foram lidas %d linhas válidas do ficheiro produtos.txt\n",pLidos);

    
    int cLidos = guardaClientes(clientesFicheiro,catc);
    printf("Foram lidas %d linhas válidas do ficheiro clientes.txt\n",cLidos);

    // ---------- Vendas -----------

    Vendas* vTodas = malloc(MAXVENDAS * sizeof *vTodas);
    Vendas* vBoas = malloc(MAXVENDAS * sizeof *vBoas);

    int vLidas = guardaVendas(vendasFicheiro,catp,catc,vTodas,vBoas,&fat);
    printf("Foram lidas %d linhas válidas do ficheiro vendas.txt\n",vLidas);

    fclose(produtoFicheiro);
    fclose(clientesFicheiro);
    fclose(vendasFicheiro);
}

void query2(Cat_Prods catp){

    Lista_Prods lp = initListaProds();
    char c;
    printf("Insira uma letra para determinar a lista e o nº total de produtos cujo código se inicia por essa letra\n");
    scanf(" %c",&c);
    lp = listaPorLetraP(catp,c);
    List_Strings ls = criaLsLp(lp);
    int tamanhoLsInit = sizeList_Strings(ls);
    printf("Houve %d produtos a começar com a letra %c.\n",tamanhoLsInit,c);
    /*for(int i = 0; getLine(getPorcao(p),i) != NULL; i++){ 
        printPag(p);
        p = getPagSeguinte(ls);
    }*/
    int page;
    printf("Que número de página pretende ler?\n");
    scanf("%d",&page);
    int numPaginas = tamanhoLsInit / 10;
    if(page > numPaginas) printf("Número de página demasiado grande\n");
    else{
        Pagina p = initPag(ls);
        for(int i = 0; i < page ; i++)
            p = getPagSeguinte(ls);
        printPag(p);
    }
}

void query3(SGV sgv,int mes, char* p){
    int nVendas = 0;
    int reader = 0; // Leitor da opção do user

    float facturadoTotal ,facturadoN ,facturadoP ; facturadoTotal  = facturadoN  = facturadoP  = 0;
    float facturado1Total,facturado1N,facturado1P; facturado1Total = facturado1N = facturado1P = 0;
    float facturado2Total,facturado2N,facturado2P; facturado2Total = facturado2N = facturado2P = 0;
    float facturado3Total,facturado3N,facturado3P; facturado3Total = facturado3N = facturado3P = 0;

    Nodo n = editNodo(mes,p);
    sgv->fat = searchF(sgv->fat,n);
    if(sgv->fat != NULL){ // Se for NULL significa que não encontrou
        Info i = getInfo(sgv->fat);

        printf("Resultado global ou filial a filial? (1/2)\n");
        scanf("%d",&reader);

        while(i != NULL){
            if(mes == getMes(i)){
                if(reader == 1) {
                    facturadoTotal += getPreco(i) * getQuant(i);
                    if(getPromo(i) == 'N') facturadoN += getPreco(i) * getQuant(i);
                    if(getPromo(i) == 'P') facturadoP += getPreco(i) * getQuant(i);
                }
                else{
                    if(getFilial(i) == 1) {
                        facturado1Total += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'N') facturado1N += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'P') facturado1P += getPreco(i) * getQuant(i);
                    }
                    if(getFilial(i) == 2){
                        facturado2Total += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'N') facturado2N += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'P') facturado2P += getPreco(i) * getQuant(i);
                    }
                    if(getFilial(i) == 3){
                        facturado3Total += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'N') facturado3N += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'P') facturado3P += getPreco(i) * getQuant(i);
                    }
                }
                nVendas++;   
            }
            i = getInfoNext(i);
        }
    }
    printf("Para o produto %s no mês %d, os resultados são os seguintes:\n",p,mes);
    printf("O número total de vendas foi: %d\n",nVendas);
    if(reader == 1) {
        printf("A faturação total foi: %f\n", facturadoTotal);
        printf("A faturação em modo N foi: %f\n", facturadoN);
        printf("A faturação em modo P foi: %f\n", facturadoP);
    }
    else {
        printf("Filial Facturação 1: %f\n",facturado1Total);
        printf("Filial Facturação 1 em modo N : %f\n",facturado1N);
        printf("Filial Facturação 1 em modo P : %f\n",facturado1P);
        printf("Filial Facturação 2: %f\n",facturado2Total);
        printf("Filial Facturação 2 em modo N : %f\n",facturado2N);
        printf("Filial Facturação 2 em modo P : %f\n",facturado2P);
        printf("Filial Facturação 3: %f\n",facturado3Total);
        printf("Filial Facturação 3 em modo N : %f\n",facturado3N);
        printf("Filial Facturação 3 em modo P : %f\n",facturado3P);
    }
}

/*void query5(SGV sgv){
    while(getFilial()){
        Lista_Clientes = ...;
    }
}*/