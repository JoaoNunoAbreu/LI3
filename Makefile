CC = gcc
CFLAGS = -Wall -ansi -O2 -std=c99
OBJFILES = funcoes catProds Produto catClientes Cliente

program: $(OBJFILES)
	$(CC) $(CFLAGS) main.c -o main funcoes.o catProds.o Produto.o catClientes.o Cliente.o
	
funcoes:
	$(CC) $(CFLAGS) -c funcoes.c

catProds:
	$(CC) $(CFLAGS) -c catProds.c

Produto:
	$(CC) $(CFLAGS) -c Produto.c

catClientes:
	$(CC) $(CFLAGS) -c catClientes.c

Cliente:
	$(CC) $(CFLAGS) -c Cliente.c

clean:
	rm program funcoes.o