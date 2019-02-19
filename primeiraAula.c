int main(){

    FILE *clientes = fopen("Clientes.txt" , "r");
    FILE *produtos = fopen("Produtos.txt" , "r");
    FILE *vendas   = fopen("Vendas_1M.txt" , "r");

    char* listaClientes[20000];
    char* listaProdutos[200000];
    char* listaVendas[1000000];

    char strClientes[5];
    char strProdutos[6];
    char strVendas[1024]; // Usar depois tamanho da linha maior.

    for(int i = 0; i < 20000; i++){
        fgets(strClientes,5,clientes);
    }

    fclose(clientes);
    fclose(produtos);
    fclose(vendas);

}