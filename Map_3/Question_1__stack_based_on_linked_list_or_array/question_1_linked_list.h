#define MAX_SIZE 4

static int last_index = 0;
static int* last = &last_index;

typedef struct node {
	int value;
	struct node *next;
} Node_stack;


void push_Llist(Node_stack** s, int x);
int pop_Llist(Node_stack** s, Node_stack* a);
int isFull_Llist(Node_stack* s);
int isEmpty_Llist(Node_stack* s);
