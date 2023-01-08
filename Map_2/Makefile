CC = gcc

CFLAGS = -c

main: main.o Question_1/question_1.o Question_2/question_2.o Question_3/question_3.o Question_5/question_5.o

main.o: main.c Question_1/question_1.c Question_2/question_2.c Question_3/question_3.c Question_5/question_5.c Map_2.h

Question_1/question_1.o: Question_1/question_1.c Map_2.h 

Question_2/question_2.o: Question_2/question_2.c Map_2.h

Question_3/question_3.o: Question_3/question_3.c Map_2.h 

Question_5/question_5.o: Question_5/question_5.c Map_2.h 

run: main
	./main
	
clean: 
	$(RM) *.o ./main ./Question_1/*.o ./Question_2/*.o ./Question_3/*.o ./Question_5/*.o