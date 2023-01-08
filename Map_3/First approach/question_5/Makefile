CC = gcc

CFLAGS = -c

main: main.o two_way_l_list.o

main.o: main.c two_way_l_list.c two_way_l_list.h

two_way_l_list.c.o: two_way_l_list.c two_way_l_list.h

run: main
	./main
	
clean: 
	$(RM) *.o ./main
