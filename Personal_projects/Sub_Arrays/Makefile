

CC = gcc

CFLAGS = -c

main: main.o SubArrays.o

main.o: main.c SubArrays.c SubArrays.h

SubArrays.o: SubArrays.c SubArrays.h

run: main
	./main
	
clean: 
	$(RM) *.o ./main
