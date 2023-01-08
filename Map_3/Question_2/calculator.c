#include <stdio.h> 
#include <stdlib.h>
#include "calculator.h"


/* Push a number (as a char *) to the stack */
void push_calc(char* element) {
    *(stack + stk_ptr) = element;
    ++stk_ptr;
}


/* Pop a number (as a char *) from the stack */       
char* pop_calc() {
    char* res =  *(stack + stk_ptr - 1);
    --stk_ptr;
    return res;
}


/* The main function - taking two 'char's *' from the stack, convert them to a numbers,/
and performing the computational operation - acoording to the input, and finally insertion the result /
to stack (as a char *) */
void calculating(char operator) {
    char* str_1 = pop_calc();
    char* str_2 = pop_calc();

    int operand_1 = atoi(str_1);
    int operand_2 = atoi(str_2);

    int res = 0;

    switch (operator)
    {
    case ('+'):
        res = operand_1 + operand_2;
        break;
    case ('-'):
        res = operand_1 - operand_2;
        break;
    case ('x'):
        res = operand_1 * operand_2;
        break;
    case ('/'):
        res = operand_1 / operand_2;
        break;
    }
 
    int string = snprintf( NULL, 0, "%d", res );
    char* str = malloc( string + 1 );
    snprintf( str, string + 1, "%d", res );
    
    push_calc(str);

}

