#include <stdio.h>
#include <stdlib.h>
#include "hash.h"


int main() {

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

    return 0;
}