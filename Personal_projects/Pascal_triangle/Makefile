

CC = gcc

CFLAGS = -c

main: main.o Pascal_Triangle.o

main.o: main.c Pascal_Triangle.c Pascal.h

Pascal_Triangle.o: Pascal_Triangle.c Pascal.h

run: main
	./main
	
clean: 
	$(RM) *.o ./main
