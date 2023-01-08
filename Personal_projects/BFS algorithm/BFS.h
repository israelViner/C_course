#define ARRAY_SIZE 6


/*  A node object for the graph (including an array of pointers to all the nodes linked to it) */
typedef struct node {
	int value;
    int parent;
    int explore;
    int number_of_neighbors;
    struct node **neighbors_array;
} Vertex;

/* Static array for the graph */
static Vertex **graph;

/* The static variables for the queue */
static int enq = 0;
static int denq = 0;
static int last = -1;
static Vertex ** QUEUE;


/* The functions for the graph */
void bfs_scan(Vertex **graph);
void print_parents(Vertex **graph);
Vertex create_Vertex(int name);
void determining_neighborhoods(Vertex **graph, Vertex *node);
void print_graph(Vertex **graph);

/* The functions for the queue */
int enqueue(Vertex **Q, Vertex *node);
Vertex *denqueue(Vertex **Q);
int isFull_array();
int isEmpty_array();