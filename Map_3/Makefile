CC = gcc

CFLAGS = -c

main: main.o Question_1/question_1_stack.o Question_1/question_1_linked_list.o \
Question_2/calculator.o Question_3/binary_tree.o \
Question_4/hash.o Question_5/two_way_l_list.o Question_6/arrays.o

main.o: main.c Question_1/question_1_stack.c Question_1/question_1_stack.h \
Question_1/question_1_linked_list.c Question_1/question_1_linked_list.h \
Question_2/calculator.c Question_2/calculator.h \
Question_3/binary_tree.c Question_3/binary_tree.h \
Question_4/hash.c Question_4/hash.h \
Question_5/two_way_l_list.c Question_5/two_way_l_list.h \
Question_6/arrays.c Question_6/arrays.h

Question_1/question_1_stack.o: Question_1/question_1_stack.c Question_1/question_1_stack.h

Question_1/question_1_linked_list.o: Question_1/question_1_linked_list.c Question_1/question_1_linked_list.h

Question_2/calculator.o: Question_2/calculator.c Question_2/calculator.h

Question_3/binary_tree.o: Question_3/binary_tree.c Question_3/binary_tree.h

Question_4/hash.o: Question_4/hash.c Question_4/hash.h

Question_5/two_way_l_list.o: Question_5/two_way_l_list.c Question_5/two_way_l_list.h

Question_6/arrays.o: Question_6/arrays.c Question_6/arrays.h

run: main
	./main $(ARGV)
	
clean: 
	$(RM) *.o ./main ./Question_1/*.o ./Question_2/*.o ./Question_3/*.o ./Question_4/*.o \
	./Question_5/*.o ./Question_6/*.o