#include <stdio.h>
#include <stdlib.h>
#include "question_1_linked_list.h"


int main() {

	int x, y, z, i, d, v;

	/* Initialize the stack */
	Node_stack* stack_1 = NULL;
	printf("is last is: %d\n", *last);
		
	/* The process of insertion an elements (4, 3, 2, 6, 7) to the stack /
	(with size of *4*) and taking them out  */
	push_Llist(&stack_1, 4);
	push_Llist(&stack_1, 3);
	printf("is full: %d\n", isFull_Llist(stack_1));
	push_Llist(&stack_1, 2);
	push_Llist(&stack_1, 6);
	push_Llist(&stack_1, 7);
	printf("is full: %d\n", isFull_Llist(stack_1));
		
	x = pop_Llist(&stack_1, stack_1);
	y = pop_Llist(&stack_1, stack_1);
	printf("is empty: %d\n", isEmpty_Llist(stack_1));
	
	z = pop_Llist(&stack_1, stack_1);
	d = pop_Llist(&stack_1, stack_1);
	pop_Llist(&stack_1, stack_1);
	printf("is empty: %d\n", isEmpty_Llist(stack_1));
	
	printf("The first element to exit was: %d, the second was: %d, the third: %d, and the forth: %d\n", x, y, z, d);
	
	return 0;
}
