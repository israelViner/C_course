#include <stdio.h>
#include <stdlib.h>
#include "two_way_l_list.h"


/* Insert an element to the head of the linked-list */
CellPtr insert_first (CellPtr list, int input) {
    Cell* p = (Cell*)malloc(sizeof(Cell));
	p->next = list;
    p->prev = NULL;
	p->contents = input;
	if (list)
        list->prev = p;
    return p; 
}


/* Print all the elements in the list (head to tail) */
void print_list (CellPtr list) {
    CellPtr p = list;
    while (p) {
        printf("%d -> ", p->contents);
        p = p->next;
    }
}


/* Printing all the elements in the list (tail to head) */
void print_rev(CellPtr list) {
    CellPtr p = list;
    while (p->next != NULL) {
        p = p->next;
    }
    while (p) {
        printf("%d -> ", p->contents);
        p = p->prev;
    }
}


/* Remove the first element from the list, free his place, and return his value */
CellPtr remove_first (CellPtr list, int *output) {
    CellPtr p = list;
    *output = p->contents;
    p = p->next;
    p->prev = NULL;
    free(list);
    return p;
}
