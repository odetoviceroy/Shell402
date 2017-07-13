.SUFFIXES: .c .o

CC = gcc

CFLAGS = -g

.c.o:
	$(CC) $(CFLAGS) -c $<

all: shell402 list create

shell402: shell402.o shell402functs.o input.o
	gcc shell402.o shell402functs.o input.o -o shell402

shell402.o: shell402.c shell402functs.h
	gcc -c shell402.c

shell402functs.o: shell402functs.c shell402functs.h macros.h
	gcc -c shell402functs.c

input.o: input.c input.h
	gcc -c input.c

list: list.o listfuncts.o
	gcc list.o listfuncts.o -o list

list.o: list.c listfuncts.h
	gcc -c list.c

listfuncts.o: listfuncts.c listfuncts.h
	gcc -c listfuncts.c

create: create.o createfuncts.o
		gcc create.o createfuncts.o -o create

create.o: create.c createfuncts.h
		gcc -c create.c

createfuncts.o: createfuncts.c createfuncts.h
		gcc -c createfuncts.c

clean:
	rm -f *.o core
