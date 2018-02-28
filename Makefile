CC = gcc

CFLAGS = -Wall -pedantic -ansi -g -std=c99

LD = gcc

LDFLAGS =

all: mytar

mytar: main.o direct.o table.o create.o
	$(LD) $(CFLAGS) -o mytar main.o direct.o table.o create.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c 

direct.o: direct.c
	$(CC) $(CFLAGS) -c direct.c

table.o: table.c
	$(CC) $(CFLAGS) -c table.c

create.o: create.c
	$(CC) $(CFLAGS) -c create.c

clean: 
	rm -f *.o mytar
