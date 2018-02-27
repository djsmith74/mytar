CC = gcc

CFLAGS = -Wall -pedantic -ansi -g -std=c99

LD = gcc

LDFLAGS =

all: mytar

mytar: main.o direct.o table.o
	$(LD) $(CFLAGS) -o mytar main.o direct.o table.o

main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c

direct.o: direct.c direct.h
	$(CC) $(CFLAGS) -c direct.c

table.o: table.c table.h
	$(CC) $(CFLAGS) -c table.c

clean: 
	rm -f *.o mytar
