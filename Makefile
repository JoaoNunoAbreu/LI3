CC = gcc
CFLAGS = -Wall -ansi -O2 -std=c99
OBJFILES = funcoes catProds Produto

program: $(OBJFILES)
	$(CC) $(CFLAGS) main.c -o main funcoes.o catProds.o Produto.o
	
funcoes:
	$(CC) $(CFLAGS) -c funcoes.c

catProds:
	$(CC) $(CFLAGS) -c catProds.c

Produto:
	$(CC) $(CFLAGS) -c Produto.c

clean:
	rm program funcoes.o