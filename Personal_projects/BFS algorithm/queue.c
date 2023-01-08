#include <stdio.h>
#include <stdlib.h>
#include "BFS.h"


/* Insert an element to the queue */
int enqueue(Vertex **Q, Vertex *node) {
	if (last == ARRAY_SIZE - 1) {
		printf("The queue is full\n");
		return 0;
	}
	else {
		*(Q + enq) = node;
        node->explore = 1;
        enq = (enq + 1) % ARRAY_SIZE;
        last += 1;
	return 1;
	}       
}
        

/* Take out an element from the queue (take the element and delete it from the queue) */       
Vertex *denqueue(Vertex **Q) {
	if (last < 0) {
        printf("The queue is empty\n");
		return NULL;
	}
    else {
		Vertex *node = *(Q + denq);
        //node = ;
		denq = (denq + 1) % ARRAY_SIZE;
        last -= 1;
        //printf("The 'denq' after the taking out is: %d\n", denq);
		return node;
	}
}
 

/* Checking if the stack is full */
int isFull_array() {
	if (last == ARRAY_SIZE - 1) 
		return 1;
	else
		return 0;
}
    

/* Checking if the stack is empty */
int isEmpty_array() {
	if (last < 0)
		return 1;
	else
		return 0;
}