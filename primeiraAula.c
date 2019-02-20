#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char listaClientes[20000][5];

    char strClientes[5];

    FILE *clientes = fopen("Clientes.txt", "r");

    for(int i = 0; fgets(strClientes,5,clientes) ; i++){
        //printf("%s", strClientes);
        strcpy(listaClientes[i],strClientes);
        printf("%s", listaClientes[i]);
    }

    fclose(clientes);

    return 0;
}
