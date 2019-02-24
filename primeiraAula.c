#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// ------------------------------------ Funções úteis globais -------------------------------------

// Dada uma linha da lista com "c" colunas, guarda na string "str" a linha "line".
void getLine(int line, int c, char lista[][c], char *str){

    memcpy(str, &lista[line],c);
    str[c] = '\0';
}

// Procura uma linha na lista.
int elem(int l, int c, char lista[l][c], char x[c]){

    int found = 0;
    char str[c+1];

    for(int i = 0; i < l; i++){
        getLine(i,c,lista,str);
        if (strcmp(str,x) == 0) found = 1;
    }
    return found;
}

// -------------------------------------- Parte de validação --------------------------------------

/* Testa no ficheiro dos produtos e clientes se os primeiros 1/2 elementos de cada linha são letras maiúsculas
/e se os números restantes estão no suposto intervalo.*/
int validaEstrutura(int l, int c, char lista[l][c], int *invalida){

    int r = 1;
    char str[c+1];
    // Se forem produtos, c = 6 e queremos 3 posições, duas para as letras e uma para '\0'.
    // Se forem clientes, c = 5 e queremos 2 posições, uma para a letra e uma para '\0'.
    int numletras = c-4;
    char *letras = malloc((numletras+1)*sizeof(char)); // É preciso fazer malloc para se criar um array com tamanho variável.
    char nums[5]; // 4 números + '\0'

    for(int i = 0; i < l; i++){

        getLine(i,c,lista,str);
        memcpy(letras,str,numletras);
        letras[numletras] = '\0';

        for(int j = 0; j < numletras; j++){
            if(!isupper(letras[j])) {
                r = 0;
                *invalida = i+1;
            }
        }
        int num = atoi(str+numletras);
        if((c == 6 && num < 1000 && num > 9999) || (c == 5 && num < 1000 && num > 5000)){
            r = 0;
            *invalida = i+1;
        }
    }
    return r;
}

// Testa se há repetições numa lista.
int validaRep(int l, int c, char lista[l][c], int *rep){

    int r = 1;
    char str[c+1];

    for(int i = 0; i < l; i++){
        getLine(i,c,lista,str);
        if(elem(i,c,lista,str)){ 
            r = 0;
            *rep = i+1;
        }
    }
    return r;
}

// --------------------------------- Parte de guardar nas listas ----------------------------------

// Guarda os produtos/clientes e retorna a quantidade de linhas lidas.
int guarda(int l, int c, char lista[l][c],FILE *fp){

    int i;

    for (i = 0;fgets(lista[i],c+2,fp);i++);

    return i;
}

// ------------------------------------------------------------------------------------------------

#define produtosLinhas 200000
#define produtosColunas 6
#define clientesLinhas 20000
#define clientesColunas 5

int main () {

    // ----------------- Listas -----------------
    char listaProdutos[produtosLinhas][produtosColunas];
    char listaClientes[clientesLinhas][clientesColunas];
    //char listaVendas[1000000][100]; // dá seg fault porque array é demasiado grande

    // --------- Abertura dos ficheiros ---------
    FILE *produtoFicheiro = fopen("Produtos.txt","r");
    FILE *clientesFicheiro = fopen("Clientes.txt","r");
    FILE *vendasFicheiro = fopen("Vendas.txt","r");

    // ----------- Guarda nas listas ------------

    int pLidas = guarda(produtosLinhas,produtosColunas,listaProdutos,produtoFicheiro);
    printf("Foram lidas %d linhas do ficheiro produtos.txt\n",pLidas);

    //int cLidas = guarda(clientesLinhas,clientesColunas,listaClientes,clientesFicheiro);
    //printf("Foram lidas %d linhas do ficheiro clientes.txt\n",cLidas);
    
    // --------------- Validação ----------------

    /*int rep1 = 0;

    // Demora muito tempo.

    if(validaRep(pLidas,produtosColunas,listaProdutos,&rep1)) printf("Não há repetições nos produtos.\n");
    else printf("Há repetições nos produtos e a linha que se repete é %d.\n",rep1);*/

    /*int rep2 = 0;

    //if(validaRep(cLidas,clientesColunas,listaClientes,&rep2)) printf("Não há repetições nos clientes.\n");
    //else printf("Há repetições nos clientes e a linha que se repete é %d.\n",rep2);*/

    int x1 = 0;

    if(validaEstrutura(pLidas,produtosColunas,listaProdutos,&x1)) printf("A estrutura dos produtos é válida.\n");
    else {
        printf("A estrutura dos produtos não é válida e a linha inválida é %d.\n",x1);
    }

    /*int x2 = 0;

    if(validaEstrutura(cLidas,clientesColunas,listaClientes,&x2)) printf("A estrutura dos clientes é válida.\n");
    else {
        printf("A estrutura dos clientes não é válida e a linha inválida é %d.\n",x2);
    }*/

    // ---------- Close dos ficheiros -----------

    fclose(produtoFicheiro);
    fclose(clientesFicheiro);
    fclose(vendasFicheiro);

    return 0;

}

/*
    NOTA:

    Validade de produtos (AB1234)
        - 2 letras maiúsculas
        - 4 dígitos entre 1000 e 9999
        - Sem repetidos (acho)

    Validade de clientes (A1234)
        - 1 letra maiúscula
        - 4 dígitos entre 1000 e 5000
        - Sem repetidos (acho)

    Validade de vendas (AB1234 123.12 123 N A1234 1 1)
        - Código de produto
        - Preço por unidade decimal entre 0.0 e 999.99
        - Número de unidades compradas entre 1 e 200
        - Compra normal ou promoção (N ou P)
        - Código do cliente
        - Mês da compra
        - Filial entre 1 e 3
        - Sem repetidos (acho)

    Objetivos:
        - Validar todas as componentes 
        - Armazenar apenas estas
        - Arranjar o melhor tamanho para o buffer do fgets()
        - Para validação das vendas fazer parsing de cada linha usando função strtok()
        - Guardar num ficheiro texto apenas as vendas válidas
        - Contar o total de dados válidos

*/