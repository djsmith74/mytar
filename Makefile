CC = gcc

CFLAGS = -Wall -pedantic -ansi -g

LD = gcc

LDFLAGS =

all: mytar

mytar: main.o direct.o
	$(LD) $(CFLAGS) -o mytar main.o direct.o

main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c

direct.o: direct.c direct.h
	$(CC) $(CFLAGS) -c direct.c

clean: 
	rm -f *.o mytar
