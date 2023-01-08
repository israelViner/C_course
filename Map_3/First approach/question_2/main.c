#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "calculator.h"


int main(int argc, char* argv[]) {

    /* Taking the numbers argoments from the command line, and push them to the stack */
    int i;
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
    printf("The result is: %s\n", pop_calc());   
    
    return 0;    
 }
