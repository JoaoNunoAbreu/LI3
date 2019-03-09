#include "funcoes.h"

char* listaProdutos[MAXPRODS];
char* listaClientes[MAXCLIENT];
char* listaVendas[MAXVENDAS];

int main(int argc, char** argv) {

    /* -------------------------------------- Medição Texec -------------------------------------*/

    clock_t start, end;
    double cpu_time_used;
    start = clock();

    /* ---------------------------------- Abertura dos ficheiros --------------------------------*/

    FILE *produtoFicheiro = fopen("Produtos.txt","r");
    if(produtoFicheiro == NULL) {printf("Produtos.txt não foi possível ser carregado."); exit (1);}
    FILE *clientesFicheiro = fopen("Clientes.txt","r");
    if(clientesFicheiro == NULL) {printf("Clientes.txt não foi possível ser carregado."); exit (1);}
    FILE *vendasFicheiro = fopen("Vendas_1M.txt","r");
    if(vendasFicheiro == NULL) {printf("Vendas.txt não foi possível ser carregado."); exit (1);}

    /* ------------------------------------ Guarda nas listas -----------------------------------*/

    int pLidos = guardaProdutos(produtoFicheiro,listaProdutos);
    printf("Foram lidas %d linhas válidas do ficheiro produtos.txt\n",pLidos);

    int cLidos = guardaClientes(clientesFicheiro,listaClientes);
    printf("Foram lidas %d linhas válidas do ficheiro clientes.txt\n",cLidos);

    /* --------- Vendas ---------*/

    Vendas* vTodas = malloc(MAXVENDAS * sizeof *vTodas);
    Vendas* vBoas = malloc(MAXVENDAS * sizeof *vBoas);

    int vLidas = guardaVendas(vendasFicheiro,listaVendas,listaProdutos,listaClientes,vTodas,vBoas);
    printf("Foram lidas %d linhas válidas do ficheiro vendas.txt\n",vLidas);

    /*printf("O último cliente (válido) foi: %s\n",vBoas[vLidas-1].cliente);
    printf("Este cliente fez %d vendas\n",contaVendas(vBoas,vBoas[vLidas-1].cliente));
    printf("Foram feitas %d vendas na filial 1\n",contaFilial(vBoas,1));
    printf("A faturação total foi: %f\n",contaFaturacao(vBoas));
    printf("O número de produtos envolvidos foi: %d\n", contaProdutosEnvolvidos(vBoas,vLidas));
    printf("O número de clientes envolvidos foi: %d\n", contaClientesEnvolvidos(vBoas,vLidas));*/

    /* ----------------------------------- Close dos ficheiros ----------------------------------*/

    fclose(produtoFicheiro);
    fclose(clientesFicheiro);
    fclose(vendasFicheiro);

    /* ------------------------------------- Medição Texec --------------------------------------*/

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("CPU Time:%f segundos.\n", cpu_time_used);

    return 0;
}