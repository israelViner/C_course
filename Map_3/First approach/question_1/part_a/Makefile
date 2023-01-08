

CC = gcc

CFLAGS = -c

main: main.o question_1_stack.o

main.o: main.c question_1_stack.c question_1_stack.h

question_1_stack.o: question_1_stack.c question_1_stack.h

run: main
	./main
	
clean: 
	$(RM) *.o ./main
