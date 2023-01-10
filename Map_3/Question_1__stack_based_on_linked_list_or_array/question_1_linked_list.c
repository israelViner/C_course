#include <stdlib.h>
#include <stdio.h>
#include "question_1_linked_list.h"


/* Push an element to the stack */
void push_Llist(Node_stack** s, int x) {
    if (*(last) == MAX_SIZE) {
            printf("The stack is full\n");
			return;
	}
    else {
		*last += 1;
		printf("The 'last' after the insertion is: %d\n", *last);
		Node_stack* p = (Node_stack*)malloc(sizeof(Node_stack));
		p->next = *s;
		p->value = x;
		*s = p;
	}       
}
        

/* Pop an element from the stack (take the element and delete it from the stack) */       
int pop_Llist(Node_stack** s, Node_stack* a) {
	if (*(last) > 0) {
		int i = a->value;
		*s = (a->next);
        	*last -= 1;
			printf("The 'last' after the taking out is: %d\n", *last);
        	return i;
	}
	else {
		printf("The stack is empty\n");
		return -1;
	}	
}


/* Checking if the stack is full */
int isFull_Llist(Node_stack* s) {
        printf("The last is: %d\n", *(last));
        if (*(last) == MAX_SIZE)
           return 1;
        else
           return 0;
}
    

/* Checking if the stack is empty */
int isEmpty_Llist(Node_stack* s) {
        if (*(last) <= 0)
           return 1;
        else
           return 0;
}