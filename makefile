.SUFFIXES: .c .o

CC = gcc

CFLAGS = -g

.c.o:
	$(CC) $(CFLAGS) -c $<

all: shell402 #list create

# TODO: retype input.o into shell402 exec file
shell402: shell402.o shell402functs.o
	gcc shell402.o shell402functs.o -o shell402

shell402.o: shell402.c shell402functs.h
	gcc -c shell402.c

shell402functs.o: shell402functs.c shell402functs.h
	gcc -c shell402functs.c

#input.o: input.c input.h
	#gcc -c input.c

#list: list.o listFunctions.o
	#gcc list.o listFunctions.o -o list

#list.o: list.c listFunctions.h
	#gcc -c list.c

#listFunctions.o: listFunctions.c listFunctions.h
	#gcc -c listFunctions.c

#create: create.o createFunctions.o
		#gcc create.o createFunctions.o -o create

#create.o: create.c createFunctions.h
		#gcc -c create.c

#createFunctions.o: createFunctions.c createFunctions.h
		#gcc -c createFunctions.c

clean:
	rm -f *.o core
