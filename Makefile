CC = gcc
CFLAGS = -Wall -ansi -O2 -std=c99
OBJFILES = catProds Produto catClientes Cliente AVL Facturacao SGV Pagina

program: $(OBJFILES)
	$(CC) $(CFLAGS) main.c -o main catProds.o Produto.o catClientes.o Cliente.o AVL.o Facturacao.o SGV.o Pagina.o

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

SGV:
	$(CC) $(CFLAGS) -c SGV.c

Pagina:
	$(CC) $(CFLAGS) -c Pagina.c	

clean:
	rm program funcoes.o