

CC = gcc

CFLAGS = -c

main: main.o queue.o BFS.o

main.o: main.c queue.c BFS.h

queue.o: queue.c BFS.h

BFS.o: BFS.c BFS.h

run: main
	./main
	
clean: 
	$(RM) *.o ./main
