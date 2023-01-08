#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include "Question_1/question_1_stack.h"
#include "Question_1/question_1_linked_list.h"
#include "Question_2/calculator.h"
#include "Question_3/binary_tree.h"
#include "Question_4/hash.h"
#include "Question_5/two_way_l_list.h"
#include "Question_6/arrays.h"


int main(int argc, char* argv[]) {

    int x, y, z, d, v, i;
    
    /* Question 1 part A */
    printf("\nQuestion 1 part A (Implement of stack with an array with size of *4*. The order of entry is: 5, 3, 2, 6, 7):\n\n");
	
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
	printf("\n");

    /* Question 1 part B */
    printf("\nQuestion 1 part B (Implement of stack with a linked list with limit size of *4*. The order of entry is: 4, 3, 2, 6, 7):\n\n");

	//* Initialize the stack */
	Node_stack* stack_1 = NULL;
	printf("The 'last' is: %d\n", *last);
		
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
    printf("\n");


    /* Question 2 */
    printf("\nQuestion 2 (Implement a calculator with a stack). The template to enter the numbers and the operators in the command line is: ARGV = <num> <num> <operator>:\n\n");
    

    /* Taking the numbers argoments from the command line, and push_array them to the stack */
    for (i = 1; i < argc; ++i) {
        if (!(*(*(argv + i)) >= 48 && *(*(argv +i)) <= 57))
            break;
        else
            push_calc(*(argv + i));    
    }
    
    /* Sending the operators from the command line (one by one) to the calculator */
    for (i; i < argc; ++i) {
        calculating(*(*(argv + i)));
    }

    /* Printing the result */
    printf("The result is: %s\n\n", pop_calc());  


     /* Question 3 */
    printf("\nQuestion 3 (Creation and management of a Binary-search-tree):\n\n"); 

    /* Create the tree and insert the element from an array to the tree */
    int array1[] = {5,3,8,1,4,9};
    int N = sizeof(array1)/sizeof(int);
    Node_tree *root = NULL;
    for(i=0; i<N; ++i)
        insert(&root,array1[i]);
    
    /* Checking the 6 functions of the tree */
    printf("Printing the nodes that inserted to the tree:\n"); 
    printTree(root);
    printf("\nSearching if the numbers between 1 and 10 is in the tree:\n"); 
    for(i=1; i<=10; ++i)
        if(isIn(root,i))
            printf("%d is in the tree.\n",i);
    printf("\nTree Height: %d\n", treeHeight(root));
    printf("\nNumber of nodes: %d \n", numOfNodes(root));
    freeTree(root);
    //printTree(root);
    printf("\n");


    /* Question 4 */
    printf("\nQuestion 4 (Adding function undef to a hash-table):\n");
 
    /* Initialize a hash-table */
    struct nlist *hashtab = NULL;

    /* Add names & definition to the hash-table */
    char name1[] = "israel";
    char defn1[] = "programer";
    char name2[] = "moyshi";
    char defn2[] = "programer";
    char name3[] = "baruch";
    char defn3[] = "programer";
    char name4[] = "menachem";
    char defn4[] = "programer";
    install(name1, defn1);
    install(name2, defn2);
    install(name3, defn3);
    install(name4, defn4);

    /* Print the hash-table before and after the deletion of an element */
    printf("\nThe list before the taking out is: \n\n");
    print_hash();
    undef(name2);    
    printf("\nThe list after the taking out is: \n\n");
    print_hash(); 
    printf("\n");


    /* Question 5*/
    printf("\nQuestion 5 (Print, Print-reverse and Ramove-first-element from a two-way-linked-list):\n\n");

    /* Initialization a two-way-linked_list & insretion four elements to the list */
    CellPtr ptr = NULL;
	ptr = insert_first (ptr, 6);
    ptr = insert_first (ptr, 5);
    ptr = insert_first (ptr, 4);
    ptr = insert_first (ptr, 8);

    /* Checking the functions (print, print-reverse,remove-first-element) */
    printf("The list is: \n");
    print_list (ptr);
    printf("\n\nThe rev list is: \n");
    print_rev(ptr);
    int a;
    int* l = &a;
    ptr = remove_first (ptr, l);
    printf("\n\nThe element %d removed\n", *l);
    printf("\nNow the list is: \n");
    print_list (ptr);
    printf("\n\n");


    /* Question 6 part A */
    printf("\nQuestion 6 part A (Finding the largest possible product between 2 elements in the array ):\n\n");

    int arr2[] = {-35, -50, 74, 20, 15};
    int max_pro = find_max_product(arr2, 5);
    printf("The max product of the array is: %d\n", max_pro);


    /* Question 6 part B */
    printf("\nQuestion 6 part A (Finding the element that divides an array):\n\n");

    int array3[] = {11, 5, 9, 8, 2, 6};
    int divides = find_divides_element(array3, 6);
    if (divides != INT_MIN)
        printf("The divides element is: %d\n\n", divides);
    else 
        printf("There is no divides element for this array\n\n");

    return 0;
}