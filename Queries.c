#include "Queries.h"

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

int validaVendas(char* linhaVenda, Cat_Prods catp, Cat_Clientes catc){

    int r = 1;
    char** tokensArray = tokenizeLinhaVendaDyn(linhaVenda);

    if(atof(tokensArray[1]) < 0 || atof(tokensArray[1]) > 999.99) r = 0;
    if(r == 1 && (atoi(tokensArray[2]) < 0 || atoi(tokensArray[2]) > 200)) r = 0;
    if(r == 1 && (*tokensArray[3] != 'N'   && *tokensArray[3] != 'P')) r = 0;
    if(r == 1 && (atoi(tokensArray[5]) < 0 || atoi(tokensArray[5]) > 12)) r = 0;
    if(r == 1 && (atoi(tokensArray[6]) < 0 || atoi(tokensArray[6]) > 3)) r = 0;
    if(r == 1 && (!existeCliente(catc,criaCliente(tokensArray[4])))) r = 0;
    if(r == 1 && (!existeProd(catp,criaProd(tokensArray[0])))) r = 0;

    return r;
}

int guardaVendas(FILE *fp, Cat_Prods catp, Cat_Clientes catc,Facturacao* fat, Filial fil[3]){

    FILE *vValidasFicheiro = fopen("Vendas_1MValidas.txt","w");
    char str[32];
    char* linha; 
    int index = 0;
    int fail = 0; // conta quantas linhas inválidas foram lidas

    while(fgets(str,32,fp)){
        linha = strtok(str,"\n\r");
        if(validaVendas(linha,catp,catc)){
            *fat = insertF(*fat,mkNodoVenda(linha));
            int i = (int) (linha[strlen(linha)-1]) - 49; // Transforma a filial da linha da venda em int
            fil[i] = insertFi(fil[i],mkNodeVenda(linha));
            fprintf(vValidasFicheiro,"%s\n",strdup(linha)); //Escreve no ficheiro vendas válidas
        }
        else fail++;
        index++;
    }
    return index-fail;
}

// ------------------------------------------------------------------------------------------------

void query1(SGV sgv){
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
    else if(c == 'n') file_name = "Produtos.txt";
    else {printf("Char inserido inválido\n");exit(1);}
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
    else if(c == 'n') file_name = "Clientes.txt";
    else {printf("Char inserido inválido\n");exit(1);}
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
    else if(c == 'n') file_name = "FicheirosTeste/testeVendas2.txt";
    else {printf("Char inserido inválido\n");exit(1);}
    FILE *vendasFicheiro = fopen(file_name,"r");
    if(vendasFicheiro == NULL) {printf("Vendas.txt não foi possível ser carregado.\n"); exit (1);}
    else printf("Ficheiro %s lido com sucesso\n",file_name);

    // --------- Catálogos ---------

    int pLidos = guardaProdutos(produtoFicheiro,getCatp(sgv));
    printf("Foram lidas %d linhas válidas do ficheiro produtos.txt\n",pLidos);
    
    int cLidos = guardaClientes(clientesFicheiro,getCatc(sgv));
    printf("Foram lidas %d linhas válidas do ficheiro clientes.txt\n",cLidos);

    // ---------- Vendas -----------

    Facturacao f = getFat(sgv);
    Filial* fil = getFilial(sgv);
    int vLidas = guardaVendas(vendasFicheiro,getCatp(sgv),getCatc(sgv),&f,fil);
    printf("Foram lidas %d linhas válidas do ficheiro vendas.txt\n",vLidas);
    setFat(sgv,f);

    fclose(produtoFicheiro);
    fclose(clientesFicheiro);
    fclose(vendasFicheiro);
}

void query2(SGV sgv){

    Lista_Prods lp = initListaProds();
    char c;
    printf("Insira uma letra para determinar a lista e o nº total de produtos cujo código se inicia por essa letra\n");
    scanf(" %c",&c);
    lp = listaPorLetraP(getCatp(sgv),c);
    List_Strings ls = criaLsLp(lp);

    // --------------------- Por colocar no navegador ---------------------
    int tamanhoLsInit = sizeList_Strings(ls);
    printf("Houve %d produtos a começar com a letra %c.\n",tamanhoLsInit,c); 
    int page = 0;
    int numPaginas = tamanhoLsInit / 10; 

    while(page >= 0){
        printf("Que número de página pretende ler? (para parar inserir número negativo)\n");
        scanf("%d",&page);
        if(page > numPaginas) printf("Número de página demasiado grande\n");
        else if(page >= 0){
            Pagina p = NULL;
            if(page == 0) p = initPag(ls);
            else{
                List_Strings tmp = criaLsLp(lp);
                for(int i = 0; i < page ; i++)
                    p = getPagSeguinte(tmp);
            }
            printPag(p);
        }
    }
    // --------------------------------------------------------------------
}

void query3(SGV sgv,int mes, char* p){
    int nVendas = 0;
    int reader = 0; // Leitor da opção do user

    float facturadoTotal ,facturadoN ,facturadoP ; facturadoTotal  = facturadoN  = facturadoP  = 0;
    float facturado1Total,facturado1N,facturado1P; facturado1Total = facturado1N = facturado1P = 0;
    float facturado2Total,facturado2N,facturado2P; facturado2Total = facturado2N = facturado2P = 0;
    float facturado3Total,facturado3N,facturado3P; facturado3Total = facturado3N = facturado3P = 0;

    Nodo n = editNodo(mes,p);
    Facturacao f = getFat(sgv);
    f = searchF(f,n);
    if(f != NULL){ // Se for NULL significa que não encontrou

        Info i = getInfo(f);
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
                    if(getNumFilial(i) == 1) {
                        facturado1Total += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'N') facturado1N += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'P') facturado1P += getPreco(i) * getQuant(i);
                    }
                    if(getNumFilial(i) == 2){
                        facturado2Total += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'N') facturado2N += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'P') facturado2P += getPreco(i) * getQuant(i);
                    }
                    if(getNumFilial(i) == 3){
                        facturado3Total += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'N') facturado3N += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'P') facturado3P += getPreco(i) * getQuant(i);
                    }
                }
                nVendas++;   
            }
            i = getInfoNext(i);
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
    else printf("Não foram encontradas vendas onde o produto %s foi comprado no mês %d",p,mes);
    
}

void query4(SGV sgv){
    Filial *fil = getFilial(sgv);
    inOrderFi(fil[2]);
}

void query5(SGV sgv){
    Cat_Clientes catc = getCatc(sgv);
    Lista_Clientes lc = catcToLista(catc);
    int notFound = 0;
    int numCliente = 0;
    List_Strings ls = initListaStrings();

    for(int i = 0; getListaClientes(lc)[i]; i++){
        NodoFil n = editNodoFi(getListaClientes(lc)[i]);
        notFound = 0;
        if(!searchFi(getFilial(sgv)[0],n)) notFound = 1;
        if(notFound == 0 && !searchFi(getFilial(sgv)[1],n))notFound = 1;
        if(notFound == 0 && !searchFi(getFilial(sgv)[2],n)) notFound = 1;

        if(notFound == 0){
            ls = addLinha(ls,getListaClientes(lc)[i],numCliente);
            numCliente++;
        }
    }
    printList_Strings(ls);
    printf("O número de códigos de clientes que realizaram compras em todas as filiais é: %d\n",numCliente);
}