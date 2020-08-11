CC = gcc
COMPILER_FLAGS = -std=c99
LINKER_FLAGS = -lm
OBJ_NAME = siguel


siguel: siguel.o legeo.o
	$(CC) siguel.o legeo.o qry.o svg.o lista.o $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

siguel.o: siguel.c legeo.o  qry.o qry.h legeo.h svg.o svg.h lista.o lista.h 
	$(CC) -c siguel.c

legeo.o: legeo.c legeo.h svg.o svg.h lista.o lista.h qry.c qry.o 
	$(CC) -c legeo.c

qry.o: qry.c qry.h lista.o lista.h
	$(CC) -c qry.c

svg.o: svg.c svg.h lista.o lista.h 
	$(CC) -c svg.c

lista.o: lista.c lista.h
	$(CC) -c lista.c