
#define STK_SIZE 20

static int stk_ptr = 0;
static char* stack[STK_SIZE]; /* stack and stack pointer */

void push_calc(char* element); 
char* pop_calc();
void calculating(char operator);