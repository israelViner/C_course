
CC = gcc

CFLAGS = -C

main: main.o arrays.o

main.o: main.c arrays.c arrays.h

arrays.o: arrays.c arrays.h

run: main
	./main
	
clean: 
	$(RM) *.o ./main