

CC = gcc

CFLAGS = -c

main: main.o question_1_linked_list.o

main.o: main.c question_1_linked_list.c question_1_linked_list.h

question_1_linked_list.o: question_1_linked_list.c question_1_linked_list.h

run: main
	./main
	
clean: 
	$(RM) *.o ./main
