#define ARRAY_SIZE 4

typedef struct stack {
	int LAST;
	int* STACK;
} Stack_array;

void init_stack(Stack_array *s);
int push_array(Stack_array *s, int x);
int denqueue(Stack_array *s);
int isFull_array(Stack_array s);
int isEmpty_array(Stack_array s);
