CC = gcc

CFLAGS = -c

main: main.o Question_1__arrays/question_1.o Question_2__strings/question_2.o Question_3__towers_of_Hanoi__recursion/question_3.o Question_5___double_pointers/question_5.o

main.o: main.c Question_1__arrays/question_1.c Question_2__strings/question_2.c Question_3__towers_of_Hanoi__recursion/question_3.c Question_5___double_pointers/question_5.c Map_2.h

Question_1__arrays/question_1.o: Question_1__arrays/question_1.c Map_2.h 

Question_2__strings/question_2.o: Question_2__strings/question_2.c Map_2.h

Question_3__towers_of_Hanoi__recursion/question_3.o: Question_3__towers_of_Hanoi__recursion/question_3.c Map_2.h 

Question_5___double_pointers/question_5.o: Question_5___double_pointers/question_5.c Map_2.h 

run: main
	./main
	
clean: 
	$(RM) *.o ./main ./Question_1__arrays/*.o ./Question_2__strings/*.o ./Question_3__towers_of_Hanoi__recursion/*.o ./Question_5___double_pointers/*.o
