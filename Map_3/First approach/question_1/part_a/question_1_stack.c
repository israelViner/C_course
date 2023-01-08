#include <stdio.h>
#include "question_1_stack.h"
    
    
void init_stack(Stack_array *s) {
	s->LAST = -1;
}

/* Push an element to the stack */
int push_array(Stack_array *s, int x) {
	if (s->LAST == ARRAY_SIZE - 1) {
		printf("The stack is full\n");
		return 0;
	}
	else {
		s->LAST += 1;
		printf("The last after the insertion is: %d\n", s->LAST);
		*(s->STACK + s->LAST) = x;
	return 1;
	}       
}
        

/* Pop an element from the stack (take the element and delete it from the stack) */       
int denqueue(Stack_array *s) {
	if (s->LAST > -1) {
		printf("The last after the taking out is: %d\n", s->LAST);
		int i = *(s->STACK + s->LAST);
		s->LAST -= 1;
		return i;
	}
	else {
		printf("The stack is empty\n");
		return -1;
	}
}
 

/* Checking if the stack is full */
int isFull_array(Stack_array s) {
	if (s.LAST == ARRAY_SIZE - 1)
		return 1;
	else
		return 0;
}
    

/* Checking if the stack is empty */
int isEmpty_array(Stack_array s) {
	if (s.LAST < 0)
		return 1;
	else
		return 0;
}

