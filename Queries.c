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
    printf("Foram lidas %d linhas válidas do ficheiro dos produtos\n",pLidos);
    
    int cLidos = guardaClientes(clientesFicheiro,getCatc(sgv));
    printf("Foram lidas %d linhas válidas do ficheiro dos clientes\n",cLidos);

    // ---------- Vendas -----------

    Facturacao f = getFat(sgv);
    Filial* fil = getFilial(sgv);
    int vLidas = guardaVendas(vendasFicheiro,getCatp(sgv),getCatc(sgv),&f,fil);
    printf("Foram lidas %d linhas válidas do ficheiro das vendas\n",vLidas);
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

    Facturacao f = getFat(sgv);
    f = searchF(f,p);
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

/**
 *  Percorre o catálogo de produtos e vê se cada produto está na facturção.
 *  Se não estiver, adicionar esse produto a uma lista e calcular tamanho da lista.
 */
void query4(SGV sgv){
    
    Cat_Prods catp = getCatp(sgv);
    Facturacao f = getFat(sgv);
    Lista_Prods lp = catpToLista(catp);
    int fail = 0;
    List_Strings ls = initListaStrings();

    char c;
    printf("Valores totais ou divididos pelas filiais? (t/f)\n");
    scanf(" %c",&c);
    
    if(c == 't'){
        for(int i = 0; getListaProds(lp)[i]; i++){
            if(searchF(f,getListaProds(lp)[i]) == NULL){
                ls = addLinha(ls,getListaProds(lp)[i],fail);
                fail++;
            }
        }
    }
    else if(c == 'f'){
        int reader;
        printf("Qual é a filial?\n");
        scanf(" %d",&reader);
        if(reader < 1 || reader > 3) {printf("Filial inserida inválida\n"); exit(1);}
        for(int i = 0; getListaProds(lp)[i]; i++){
            if(searchF(f,getListaProds(lp)[i]) == NULL || !procuraFilialNaInfo(getInfo(searchF(f,getListaProds(lp)[i])),reader)){
                ls = addLinha(ls,getListaProds(lp)[i],fail);
                fail++;
            }
        }
    }
    else {printf("Char inserido inválido\n");exit(1);}
    
    printList_Strings(ls);
    printf("O número de produtos que ninguém comprou foi: %d.\n",fail);
}

void query5(SGV sgv){
    Cat_Clientes catc = getCatc(sgv);
    Lista_Clientes lc = catcToLista(catc);
    int notFound = 0;
    int numCliente = 0;
    List_Strings ls = initListaStrings();

    for(int i = 0; getListaClientes(lc)[i]; i++){
        notFound = 0;
        if(!searchFi(getFilial(sgv)[0],getListaClientes(lc)[i])) notFound = 1;
        if(notFound == 0 && !searchFi(getFilial(sgv)[1],getListaClientes(lc)[i])) notFound = 1;
        if(notFound == 0 && !searchFi(getFilial(sgv)[2],getListaClientes(lc)[i])) notFound = 1;

        if(notFound == 0){
            ls = addLinha(ls,getListaClientes(lc)[i],numCliente);
            numCliente++;
        }
    }
    printList_Strings(ls);
    printf("O número de códigos de clientes que realizaram compras em todas as filiais é: %d.\n",numCliente);
}

/**
 *  Percorre os catálogos de produtos e de clientes e vê se estes estão na facturação e na filial, respetivamente.
 */
void query6(SGV sgv){
    Cat_Prods catp = getCatp(sgv);
    Lista_Prods lp = catpToLista(catp);

    Cat_Clientes catc = getCatc(sgv);
    Lista_Clientes lc = catcToLista(catc);

    int countC,countP; countC = countP = 0;

    int found = 0;
    // Nº de clientes que não realizaram compras
    for(int i = 0; getListaClientes(lc)[i]; i++){
        found = 0;
        if(searchFi(getFilial(sgv)[0],getListaClientes(lc)[i])) found = 1;
        if(found == 0 && searchFi(getFilial(sgv)[1],getListaClientes(lc)[i])) found = 1;
        if(found == 0 && searchFi(getFilial(sgv)[2],getListaClientes(lc)[i])) found = 1;

        if(found == 0) countC++;
    }
    // Nº de produtos que ninguém comprou
    for(int i = 0; getListaProds(lp)[i]; i++)
        if(searchF(getFat(sgv),getListaProds(lp)[i]) == NULL) countP++;

    printf("Nº clientes que não realizaram compras: %d\n",countC);
    printf("Nº de produtos que ninguém comprou: %d\n",countP);
}

void query7(SGV sgv, char* cliente){
    int tabela[12][3];
    for(int i = 0; i < 12; i++)
        for(int j = 0; j < 3; j++)
            tabela[i][j] = 0;

    if(searchFi(getFilial(sgv)[0],cliente)){
        InfoFil i = getInfoFil(searchFi(getFilial(sgv)[0],cliente));
        while(i != NULL){
            tabela[getMesFil(i)-1][0] += getQuantFil(i);
            i = getInfoNextFil(i);
        }
    }
    if(searchFi(getFilial(sgv)[1],cliente)){
        InfoFil i = getInfoFil(searchFi(getFilial(sgv)[1],cliente));
        while(i != NULL){
            tabela[getMesFil(i)-1][1] += getQuantFil(i);
            i = getInfoNextFil(i);
        }
    }
    if(searchFi(getFilial(sgv)[2],cliente)){
        InfoFil i = getInfoFil(searchFi(getFilial(sgv)[2],cliente));
        while(i != NULL){
            tabela[getMesFil(i)-1][2] += getQuantFil(i);
            i = getInfoNextFil(i);
        }
    }
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 3; j++)
            if(j == 2) printf("%d",tabela[i][j]);
            else printf("%d, ",tabela[i][j]);
        printf("\n");
    }            
}

void query8(SGV sgv, int mes1, int mes2){
    Facturacao f = getFat(sgv);
    int totalVendas = 0;
    float totalFaturado = 0;
    query8Aux(f,mes1,mes2,&totalVendas,&totalFaturado);
    printf("O total de vendas entre os meses %d e %d foi: %d.\n",mes1,mes2,totalVendas);
    printf("O total faturado entre os meses %d e %d foi: %f.\n",mes1,mes2,totalFaturado);
}

void query9(SGV sgv, char* produto, int filial){
    List_Strings lsN = initListaStrings();
    List_Strings lsP = initListaStrings();
    Filial fil = getFilial(sgv)[filial-1];
    int indexN,indexP; indexN = indexP = 0;
    query9Aux(fil,produto,lsN,lsP,&indexN,&indexP);
    printf("Lista dos clientes que compraram o produto %s na filial %d com promoção N\n",produto,filial);
    printList_Strings(lsN);
    printf("Lista dos clientes que compraram o produto %s na filial %d com promoção P\n",produto,filial);
    printList_Strings(lsP);
}

void query10(SGV sgv, char* cliente, int mes){
    List_Strings ls = initListaStrings();
    Lligada a = NULL;

    if(searchFi(getFilial(sgv)[0],cliente)){
        InfoFil i = getInfoFil(searchFi(getFilial(sgv)[0],cliente));
        while(i != NULL){
            if(getMesFil(i) == mes){
                push(&a,(float) getQuantFil(i),getProduto(i));
            }
            i = getInfoNextFil(i);
        }
    }
    if(searchFi(getFilial(sgv)[1],cliente)){
        InfoFil i = getInfoFil(searchFi(getFilial(sgv)[1],cliente));
        while(i != NULL){
            if(getMesFil(i) == mes){
                push(&a,(float) getQuantFil(i),getProduto(i));
            }
            i = getInfoNextFil(i);
        }
    }
    if(searchFi(getFilial(sgv)[2],cliente)){
        InfoFil i = getInfoFil(searchFi(getFilial(sgv)[2],cliente));
        while(i != NULL){
            if(getMesFil(i) == mes){
                push(&a,(float) getQuantFil(i),getProduto(i));
            }
            i = getInfoNextFil(i);
        }
    }
    int index = 0;
    MergeSort(&a);
    while(a){
        ls = addLinha(ls,getLinha(a),index);
        index++;
        a = getNext(a);
    }    
    printList_Strings(ls);
}

void query11(SGV sgv, int N){

    List_Strings ls1 = initListaStrings();
    List_Strings ls2 = initListaStrings();
    List_Strings ls3 = initListaStrings();

    Facturacao f = getFat(sgv);

    Lligada a1 = NULL;
    Lligada a2 = NULL;
    Lligada a3 = NULL;    

    query11Aux(f,&a1,1);
    query11Aux(f,&a2,2);
    query11Aux(f,&a3,3);

    for(int i = 0; i < N; i++){
        swapNodes(&a1,getKdata(a1,i),maxLligada(a1,i));
    } 

    for(int i = 0; i < N; i++){
        swapNodes(&a2,getKdata(a2,i),maxLligada(a2,i));
    }

    for(int i = 0; i < N; i++){
        swapNodes(&a3,getKdata(a3,i),maxLligada(a3,i));
    }

    // Passar isto para o navegador

    int index = 0;
    while(a1 && index < N){
        ls1 = addLinha(ls1,getLinha(a1),index);
        index++;
        a1 = getNext(a1);
    }
    index = 0;
    while(a2 && index < N){
        ls2 = addLinha(ls2,getLinha(a2),index);
        index++;
        a2 = getNext(a2);
    }
    index = 0;
    while(a3 && index < N){
        ls3 = addLinha(ls3,getLinha(a3),index);
        index++;
        a3 = getNext(a3);
    }

    int count1 = 0;
    for(int i = 0; getLine(ls1,i) != NULL; i++){
        Info info = getInfo(searchF(f,getLine(ls1,i)));
        while(info != NULL){
            count1++;
            info = getInfoNext(info);
        }
    }

    int count2 = 0;
    for(int i = 0; getLine(ls2,i) != NULL; i++){
        Info info = getInfo(searchF(f,getLine(ls2,i)));
        while(info != NULL){
            count2++;
            info = getInfoNext(info);
        }
    }

    int count3 = 0;
    for(int i = 0; getLine(ls3,i) != NULL; i++){
        Info info = getInfo(searchF(f,getLine(ls3,i)));
        while(info != NULL){
            count3++;
            info = getInfoNext(info);
        }
    }

    printf("---- Filial 1 ----\n");
    printNList(a1,N);
    printf("%d\n",count1);
    printf("---- Filial 2 ----\n");
    printNList(a2,N);
    printf("%d\n",count2);
    printf("---- Filial 3 ----\n");
    printNList(a3,N);
    printf("%d\n",count3);
}

void query12(SGV sgv, char* cliente){

    List_Strings ls = initListaStrings();
    Lligada a = NULL;

    if(searchFi(getFilial(sgv)[0],cliente)){
        InfoFil i = getInfoFil(searchFi(getFilial(sgv)[0],cliente));
        while(i != NULL){
            push(&a,getFaturadoFil(i),getProduto(i));
            i = getInfoNextFil(i);
        }
    }

    if(searchFi(getFilial(sgv)[1],cliente)){
        InfoFil i = getInfoFil(searchFi(getFilial(sgv)[1],cliente));
        while(i != NULL){
            push(&a,getFaturadoFil(i),getProduto(i));
            i = getInfoNextFil(i);
        }
    }

    if(searchFi(getFilial(sgv)[2],cliente)){
        InfoFil i = getInfoFil(searchFi(getFilial(sgv)[2],cliente));
        while(i != NULL){
            push(&a,getFaturadoFil(i),getProduto(i));
            i = getInfoNextFil(i);
        }
    }
    MergeSort(&a);
    
    int index = 0;
    while(a && index < 3){
        ls = addLinha(ls,getLinha(a),index);
        index++;
        a = getNext(a);
    }
    printList_Strings(ls);
}