CC = gcc

CFLAGS = -Wall -pedantic -ansi -g

LD = gcc

LDFLAGS =

all: mytar

mytar: main.o
	$(LD) $(CFLAGS) -o mytar main.o

main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c

clean: 
	rm -f *.o mytar
