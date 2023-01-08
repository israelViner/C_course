#include <stdio.h>
#include <stdlib.h>
#include "question_1_stack.h"

int main() {
	
	int x, y, z, d, v;

	/* Initialize the stack */
	Stack_array stack;
	init_stack(&stack);
	stack.STACK = (int*)malloc(sizeof(int)*ARRAY_SIZE);
		
	/* The process of insertion an elements (5, 3, 2, 6, 7) to the stack /
	(with size of *4*) and taking them out  */
	push_array(&stack, 5);
	push_array(&stack, 3);
	printf("is full: %d\n", isFull_array(stack));
	
	push_array(&stack, 2);
	push_array(&stack, 6);
	push_array(&stack, 7);
	printf("is full: %d\n", isFull_array(stack));
	
	x = denqueue(&stack);
	y = denqueue(&stack);
	printf("is empty: %d\n", isEmpty_array(stack));
	
	z = denqueue(&stack);
	d = denqueue(&stack);
	denqueue(&stack);
	printf("is empty: %d\n", isEmpty_array(stack));
	
	printf("The first element to exit was: %d, the second was: %d, the third: %d, and the forth: %d\n", x, y, z, d);
	
	return 0;
}
