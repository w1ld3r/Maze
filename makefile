CC=gcc
OPT=-Wall

PROJET : EXEC START NET

matrice.o : matrix.c matrix.h libraries.h
	$(CC) -c matrice.c $(OPT)

maze.o : maze.c maze.h libraries.h
	$(CC) -c maze.c $(OPT)

resolve.o : resolve.c resolve.h libraries.h
	$(CC) -c resolve.c $(OPT)

main.o : main.c libraries.h
	$(CC) -c main.c $(OPT)

EXEC : resolve.o resolve.h maze.o maze.h matrix.o matrix.h main.o libraries.h
	$(CC) -o $@ resolve.o maze.o matrix.o main.o

START :
	./EXEC

NET :
	@ rm -rf *.o
