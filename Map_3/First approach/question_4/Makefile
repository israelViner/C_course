CC = gcc

CFLAGS = -c

main: main.o hash.o

main.o: main.c hash.c hash.h

hash.c.o: hash.c hash.h

run: main
	./main
	
clean: 
	$(RM) *.o ./main
