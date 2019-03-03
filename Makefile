CC = gcc
CFLAGS = -Wall

program:funcoes
	$(CC) $(CFLAGS) main.c -o main funcoes.o

funcoes:
	$(CC) $(CFLAGS) -c funcoes.c

clean:
	rm program funcoes.o