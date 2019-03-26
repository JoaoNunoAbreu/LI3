#include "funcoes.h"

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

    /* ----------------------------------- Guarda nos catálogos ---------------------------------*/

    printf("-------------------------- Início ------------------------------\n\n");

    Cat_Prods catp = inicializa_CatProds();
    int pLidos = guardaProdutos(produtoFicheiro,catp);
    printf("Foram lidas %d linhas válidas do ficheiro produtos.txt\n",pLidos);

    Cat_Clientes catc = inicializa_CatClientes();
    int cLidos = guardaClientes(clientesFicheiro,catc);
    printf("Foram lidas %d linhas válidas do ficheiro clientes.txt\n",cLidos);

    /* --------- Vendas ---------*/

    Vendas* vTodas = malloc(MAXVENDAS * sizeof *vTodas);
    Vendas* vBoas = malloc(MAXVENDAS * sizeof *vBoas);

    int vLidas = guardaVendas(vendasFicheiro,catp,catc,vTodas,vBoas);
    printf("Foram lidas %d linhas válidas do ficheiro vendas.txt\n",vLidas);

    /* ------------------------------------------ TESTES ----------------------------------------*/

    printf("\n");
    Lista_Prods lp = initListaProds();
    lp = listaPorLetraP(catp,'A');
    printf("Houve %d produtos a começar com a letra A.\n",sizeOfLista_Prods(lp));

    Lista_Clientes lc = initListaClientes();
    lc = listaPorLetraC(catc,'A');
    printf("Houve %d produtos a começar com a letra A.\n",sizeOfLista_Clientes(lc));

    //printf("A linha mais longa das vendas foi: %d\n", contaMaiorLinha(listaVendas));
    int prodEnvolvidos = contaProdutosEnvolvidos(vBoas);
    printf("O número de produtos envolvidos foi: %d\n", prodEnvolvidos);
    printf("O número de produtos nunca comprado foi: %d\n", pLidos - prodEnvolvidos);
    int clientEnvolvidos = contaClientesEnvolvidos(vBoas);
    printf("O número de clientes envolvidos foi: %d\n",clientEnvolvidos);
    printf("O número de clientes nunca comprado foi: %d\n",cLidos - clientEnvolvidos);
    printf("Houve %d códigos de clientes inválidos nas vendas.\n",indexCI);
    printf("Houve %d códigos de produtos inválidos nas vendas.\n",indexPI);
    printf("O último cliente (válido) foi: %s\n",vBoas[vLidas-1].cliente);
    printf("Este cliente fez %d vendas\n",contaVendas(vBoas,vBoas[vLidas-1].cliente));
    printf("Foram feitas %d vendas na filial 1\n",contaFilial(vBoas,1));
    printf("Foram feitas %d vendas na filial 2\n",contaFilial(vBoas,2));
    printf("Foram feitas %d vendas na filial 3\n",contaFilial(vBoas,3));
    printf("A faturação total foi: %e\n",contaFaturacao(vBoas));
    printf("Foram vendidas %d unidades.\n",contaUnidades(vBoas));
    printf("Foram feitas %d vendas com preço 0.\n",contaPrecos(vBoas,0));
    printf("\n");

    printf("--------------------------- Fim --------------------------------\n");

    /* ----------------------------------- Close dos ficheiros ----------------------------------*/

    fclose(produtoFicheiro);
    fclose(clientesFicheiro);
    fclose(vendasFicheiro);

    /* ------------------------------------- Medição Texec --------------------------------------*/

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nCPU Time:%f segundos.\n\n", cpu_time_used);

    return 0;
}
