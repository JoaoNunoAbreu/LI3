CC = gcc
CFLAGS = -Wall -ansi -O2 -std=c99
OBJFILES = catProds Produto catClientes Cliente AVL Facturacao Filial Queries Pagina SGV LinkedList IO

program: $(OBJFILES)
	$(CC) $(CFLAGS) main.c -o main catProds.o Produto.o catClientes.o Cliente.o AVL.o Facturacao.o Filial.o Queries.o Pagina.o SGV.o LinkedList.o IO.o

catProds:
	$(CC) $(CFLAGS) -c catProds.c

Produto:
	$(CC) $(CFLAGS) -c Produto.c

catClientes:
	$(CC) $(CFLAGS) -c catClientes.c

Cliente:
	$(CC) $(CFLAGS) -c Cliente.c

AVL:
	$(CC) $(CFLAGS) -c AVL.c

Facturacao:
	$(CC) $(CFLAGS) -c Facturacao.c

Filial:
	$(CC) $(CFLAGS) -c Filial.c	

Queries:
	$(CC) $(CFLAGS) -c Queries.c

Pagina:
	$(CC) $(CFLAGS) -c Pagina.c	

SGV:
	$(CC) $(CFLAGS) -c SGV.c

LinkedList:
	$(CC) $(CFLAGS) -c LinkedList.c	

IO:
	$(CC) $(CFLAGS) -c IO.c	

clean:
	rm catProds.o Produto.o catClientes.o Cliente.o AVL.o Facturacao.o Filial.o Queries.o Pagina.o SGV.o LinkedList.o IO.o