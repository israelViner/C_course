#include <stdio.h>
#include "two_way_l_list.h"


int main() {

    /* Initialization a two-way-linked_list & insretion four elements to the list */
    CellPtr ptr = NULL;
	ptr = insert_first (ptr, 6);
    ptr = insert_first (ptr, 5);
    ptr = insert_first (ptr, 4);
    ptr = insert_first (ptr, 8);

    /* Checking the functions (print, print-reverse,remove-first-element) */
    printf("The list is: \n");
    print_list (ptr);
    printf("The rev list is: \n");
    print_rev(ptr);
    int a;
    int* x = &a;
    ptr = remove_first (ptr, x);
    printf("The element %d removed.\n", *x);
    printf("Now the list is: \n");
    print_list (ptr);
 
    return 0;
}