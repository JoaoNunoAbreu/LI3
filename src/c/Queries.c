#include "Queries.h"
#include <unistd.h>
//-----------------------------------------------------------------------------------------------

char** tokenizeLinhaVendaDyn(char* vendaRaw) {
    int index = 0;
    char** campos = (char**) malloc(7 * sizeof(char*));
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

void guardaVendas(FILE *fp, Cat_Prods catp, Cat_Clientes catc,Facturacao* fat, Filial fil[3], int* vLidas, int* vTotal){

    FILE *vValidasFicheiro = fopen("Vendas_1MValidas.txt","w");
    char str[32];
    char* linha; 

    while(fgets(str,32,fp)){
        linha = strtok(str,"\n\r");
        if(validaVendas(linha,catp,catc)){
            *fat = insertF(*fat,mkNodoVenda(linha));
            int i = (int) (linha[strlen(linha)-1]) - 49; // Transforma a filial da linha da venda em int
            fil[i] = insertFi(fil[i],mkNodeVenda(linha));
            fprintf(vValidasFicheiro,"%s\n",strdup(linha)); //Escreve no ficheiro vendas válidas
            *vLidas = *vLidas + 1;
        }
        *vTotal = *vTotal + 1;
    }
}

// ------------------------------------------------------------------------------------------------

int query1(SGV sgv, char* file_nameProds, char* file_nameClient, char* file_nameVendas, int* pLidos, int* pTotal, int* cLidos,int* cTotal, int* vLidas, int* vTotal){

    FILE *produtoFicheiro = fopen(file_nameProds,"r");
    if(produtoFicheiro == NULL) return 1;

    FILE *clientesFicheiro = fopen(file_nameClient,"r");
    if(clientesFicheiro == NULL) return 2;

    FILE *vendasFicheiro = fopen(file_nameVendas,"r");
    if(vendasFicheiro == NULL) return 3;

    // --------- Catálogos ---------

    guardaProdutos(produtoFicheiro,getCatp(sgv),pLidos,pTotal);
    guardaClientes(clientesFicheiro,getCatc(sgv),cLidos,cTotal);

    // ---------- Vendas -----------

    Facturacao f = getFat(sgv);
    Filial* fil = getFilial(sgv);
    guardaVendas(vendasFicheiro,getCatp(sgv),getCatc(sgv),&f,fil,vLidas,vTotal);
    setFat(sgv,f);

    fclose(produtoFicheiro);
    fclose(clientesFicheiro);
    fclose(vendasFicheiro);

    return 0;
}

List_Strings query2(SGV sgv, char c){

    Lista_Prods lp = initListaProds();
    lp = listaPorLetraP(getCatp(sgv),c);
    List_Strings ls = criaLsLp(lp);
    return ls;
}

void query3(SGV sgv,int mes, Produto p, char c,float* fat1T,float* fat1N,float* fat1P,float* fat2T,float* fat2N,float* fat2P, float* fat3T,float* fat3N,float* fat3P, int* nVendas){

    Facturacao f = getFat(sgv);
    f = searchF(f,getCodProd(p));
    if(f != NULL){ // Se for NULL significa que não encontrou

        Info i = getInfo(f);
        while(i != NULL){
            if(mes == getMes(i)){
                if(c == 'g'){ // Para poupar criar mais 3 variáveis
                    *fat1T += getPreco(i) * getQuant(i);
                    if(getPromo(i) == 'N') *fat1N += getPreco(i) * getQuant(i);
                    if(getPromo(i) == 'P') *fat1P += getPreco(i) * getQuant(i);
                }
                else if(c == 'f'){
                    if(getNumFilial(i) == 1) {
                        *fat1T += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'N') *fat1N += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'P') *fat1P += getPreco(i) * getQuant(i);
                    }
                    if(getNumFilial(i) == 2){
                        *fat2T += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'N') *fat2N += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'P') *fat2P += getPreco(i) * getQuant(i);
                    }
                    if(getNumFilial(i) == 3){
                        *fat3T += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'N') *fat3N += getPreco(i) * getQuant(i);
                        if(getPromo(i) == 'P') *fat3P += getPreco(i) * getQuant(i);
                    }
                }
                *nVendas = *nVendas + 1;
            }
            i = getInfoNext(i);
        }
    }
}

/**
 *  Percorre o catálogo de produtos e vê se cada produto está na facturção.
 *  Se não estiver, adicionar esse produto a uma lista e calcular tamanho da lista.
 */
List_Strings query4(SGV sgv,char c, int filial){
    
    Cat_Prods catp = getCatp(sgv);
    Facturacao f = getFat(sgv);
    Lista_Prods lp = catpToLista(catp);
    int fail = 0;
    List_Strings ls = initListaStrings();
    
    if(c == 't'){
        for(int i = 0; getListaProds(lp)[i]; i++){
            if(searchF(f,getListaProds(lp)[i]) == NULL){
                ls = addLinha(ls,getListaProds(lp)[i],fail);
                fail++;
            }
        }
    }
    else if(c == 'f'){
        if(filial >= 1 && filial <= 3) {
            for(int i = 0; getListaProds(lp)[i]; i++)
                if(searchF(f,getListaProds(lp)[i]) == NULL || !procuraFilialNaInfo(getInfo(searchF(f,getListaProds(lp)[i])),filial)){
                    ls = addLinha(ls,getListaProds(lp)[i],fail);
                    fail++;
                }
        }
    }
    return ls;
}

List_Strings query5(SGV sgv){
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
    return ls;
}

/**
 *  Percorre os catálogos de produtos e de clientes e vê se estes estão na facturação e na filial, respetivamente.
 */
void query6(SGV sgv, int* countC, int* countP){
    Cat_Prods catp = getCatp(sgv);
    Lista_Prods lp = catpToLista(catp);

    Cat_Clientes catc = getCatc(sgv);
    Lista_Clientes lc = catcToLista(catc);

    int found = 0;
    // Nº de clientes que não realizaram compras
    for(int i = 0; getListaClientes(lc)[i]; i++){
        found = 0;
        if(searchFi(getFilial(sgv)[0],getListaClientes(lc)[i])) found = 1;
        if(found == 0 && searchFi(getFilial(sgv)[1],getListaClientes(lc)[i])) found = 1;
        if(found == 0 && searchFi(getFilial(sgv)[2],getListaClientes(lc)[i])) found = 1;

        if(found == 0) *countC = *countC + 1;
    }
    // Nº de produtos que ninguém comprou
    for(int i = 0; getListaProds(lp)[i]; i++)
        if(searchF(getFat(sgv),getListaProds(lp)[i]) == NULL) *countP = *countP + 1;
}

void query7(SGV sgv, Cliente cliente,int tabela[12][3]){

    for(int i = 0; i < 12; i++)
        for(int j = 0; j < 3; j++)
            tabela[i][j] = 0;

    if(searchFi(getFilial(sgv)[0],getCodCliente(cliente))){
        InfoFil i = getInfoFil(searchFi(getFilial(sgv)[0],getCodCliente(cliente)));
        while(i != NULL){
            tabela[getMesFil(i)-1][0] += getQuantFil(i);
            i = getInfoNextFil(i);
        }
    }
    if(searchFi(getFilial(sgv)[1],getCodCliente(cliente))){
        InfoFil i = getInfoFil(searchFi(getFilial(sgv)[1],getCodCliente(cliente)));
        while(i != NULL){
            tabela[getMesFil(i)-1][1] += getQuantFil(i);
            i = getInfoNextFil(i);
        }
    }
    if(searchFi(getFilial(sgv)[2],getCodCliente(cliente))){
        InfoFil i = getInfoFil(searchFi(getFilial(sgv)[2],getCodCliente(cliente)));
        while(i != NULL){
            tabela[getMesFil(i)-1][2] += getQuantFil(i);
            i = getInfoNextFil(i);
        }
    }          
}

void query8(SGV sgv, int mes1, int mes2, int* totalVendas, float* totalFaturado){
    Facturacao f = getFat(sgv);
    query8Aux(f,mes1,mes2,totalVendas,totalFaturado);
}

void query9(SGV sgv, List_Strings lsN, List_Strings lsP, Produto produto, int filial){
    Filial fil = getFilial(sgv)[filial-1];
    int indexN,indexP; indexN = indexP = 0;
    query9Aux(fil,getCodProd(produto),lsN,lsP,&indexN,&indexP);
}

List_Strings query10(SGV sgv, Cliente cliente, int mes){
    List_Strings ls = initListaStrings();
    Lligada a = NULL;

    if(searchFi(getFilial(sgv)[0],getCodCliente(cliente))){
        InfoFil i = getInfoFil(searchFi(getFilial(sgv)[0],getCodCliente(cliente)));
        while(i != NULL){
            if(getMesFil(i) == mes){
                push(&a,(float) getQuantFil(i),getProduto(i));
            }
            i = getInfoNextFil(i);
        }
    }
    if(searchFi(getFilial(sgv)[1],getCodCliente(cliente))){
        InfoFil i = getInfoFil(searchFi(getFilial(sgv)[1],getCodCliente(cliente)));
        while(i != NULL){
            if(getMesFil(i) == mes){
                push(&a,(float) getQuantFil(i),getProduto(i));
            }
            i = getInfoNextFil(i);
        }
    }
    if(searchFi(getFilial(sgv)[2],getCodCliente(cliente))){
        InfoFil i = getInfoFil(searchFi(getFilial(sgv)[2],getCodCliente(cliente)));
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
    return ls;
}

void query11(SGV sgv, int N,List_Strings ls1,List_Strings ls2,List_Strings ls3,int* count1, int* count2, int* count3){

    Facturacao f = getFat(sgv);

    Lligada a1 = NULL;
    Lligada a2 = NULL;
    Lligada a3 = NULL;    

    query11Aux(f,&a1,1);
    query11Aux(f,&a2,2);
    query11Aux(f,&a3,3);

    MergeSort(&a1);
    MergeSort(&a2);
    MergeSort(&a3);
    
    int index = 0;
    char* line = malloc(sizeof(char*));
    while(a1 && index < N){
        getValor_Produto(a1,&line);
        ls1 = addLinha(ls1,line,index);
        index++;
        a1 = getNext(a1);
    }
    index = 0;
    while(a2 && index < N){
        getValor_Produto(a2,&line);
        ls2 = addLinha(ls2,line,index);
        index++;
        a2 = getNext(a2);
    }
    index = 0;
    while(a3 && index < N){
        getValor_Produto(a3,&line);
        ls3 = addLinha(ls3,line,index);
        index++;
        a3 = getNext(a3);
    }
    
    for(int i = 0; getLine(ls1,i) != NULL; i++){
        Info info = getInfo(searchF(f,getLine(ls1,i)));
        while(info != NULL){
            *count1 = *count1 + 1;
            info = getInfoNext(info);
        }
    }
    for(int i = 0; getLine(ls2,i) != NULL; i++){
        Info info = getInfo(searchF(f,getLine(ls2,i)));
        while(info != NULL){
            *count2 = *count2 + 1;
            info = getInfoNext(info);
        }
    }
    for(int i = 0; getLine(ls3,i) != NULL; i++){
        Info info = getInfo(searchF(f,getLine(ls3,i)));
        while(info != NULL){
            *count3 = *count3 + 1;
            info = getInfoNext(info);
        }
    }
}

List_Strings query12(SGV sgv, Cliente cliente){

    List_Strings ls = initListaStrings();
    Lligada a = NULL;

    if(searchFi(getFilial(sgv)[0],getCodCliente(cliente))){
        InfoFil i = getInfoFil(searchFi(getFilial(sgv)[0],getCodCliente(cliente)));
        while(i != NULL){
            push(&a,getFaturadoFil(i),getProduto(i));
            i = getInfoNextFil(i);
        }
    }

    if(searchFi(getFilial(sgv)[1],getCodCliente(cliente))){
        InfoFil i = getInfoFil(searchFi(getFilial(sgv)[1],getCodCliente(cliente)));
        while(i != NULL){
            push(&a,getFaturadoFil(i),getProduto(i));
            i = getInfoNextFil(i);
        }
    }

    if(searchFi(getFilial(sgv)[2],getCodCliente(cliente))){
        InfoFil i = getInfoFil(searchFi(getFilial(sgv)[2],getCodCliente(cliente)));
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
    return ls;
}