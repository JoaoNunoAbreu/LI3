#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char listaClientes[40000][5];

    FILE *clientes = fopen("Clientes.txt", "r");

    for (int i = 0;fgets(listaClientes[i],sizeof listaClientes[i],clientes); i++)
        printf("%s", listaClientes[i]);

    fclose(clientes);

    return 0;
}
