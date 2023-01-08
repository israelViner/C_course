#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "BFS.h"


/* The main function - BFS algorithm: inserting the first node (that chosen at random) into the queue (the insertion includes labeling), 
then in an iterative loop as long as the queue is not empty: removing a node from the queue, 
going through the entire list of its neighboring nodes, and if the neighboring node is not labeled - labeling, 
setting the current node as 'Parent', and put it in the queue */
void bfs_scan(Vertex **graph) {
    QUEUE = (Vertex **)malloc(sizeof(Vertex *)*ARRAY_SIZE);
    Vertex *node;

    srand(time(0));
    int num = rand() % ARRAY_SIZE;

    /* Inserting the first node to the queue (while defining his 'parent' to INT_MAX) */
    Vertex *t;
    t = *(graph + num);
    t->parent = INT_MAX;
    enqueue(QUEUE, t); 

    /* The iterative loop for all the nodes in the graph */
    while (!isEmpty_array()) {
        node = denqueue(QUEUE);
        for (int i = 0; i < (node->number_of_neighbors); ++i) {
            if (node->neighbors_array[i]->explore == 0) {
                (node->neighbors_array[i])->parent = (node->value);
                enqueue(QUEUE,  (node->neighbors_array[i]));
            }
        }
    }
    return;
}


/* Initialize a vertex on the graph */
Vertex create_Vertex(int name) {
    int lower = 2;
    int num = (rand() % (ARRAY_SIZE - lower - 1)) + lower;
    Vertex *node = (Vertex *)malloc(sizeof(Vertex));
    node->value = name;
    node->number_of_neighbors = num;
    node->explore = 0;
    node->parent = INT_MIN;
    node->neighbors_array = (Vertex**)malloc(sizeof(Vertex *) * node->number_of_neighbors);
    return *node; 
}


/* Determining the neighborhoods of a node */
void determining_neighborhoods(Vertex **graph, Vertex *node) {
    int i = 0;
    while (i < node->number_of_neighbors) {
        int exsists = 0, j = 0;
        int num = rand() % ARRAY_SIZE;
        Vertex *t = *(graph + num);
        if (t->value != node->value) {
            while (j < i) {
                if (t->value == node->neighbors_array[j]->value) 
                    exsists = 1;
                ++j;
            }
            if (!exsists) {
                (node->neighbors_array[i]) = t;
                ++i;    
            }
        }
        
    }
}


/* Printing the neighbors of each node on the graph */
void print_graph(Vertex **graph) {
    for (int j = 0; j < ARRAY_SIZE; ++j) {
        Vertex *node = *(graph + j);
        printf("\nThe neighbors of node %c their:\n", node->value);
        for (int i = 0; i < node->number_of_neighbors; ++i) {
            printf("%c,  ", (node->neighbors_array[i])->value);
        }
    }
}


/* Print the 'parent' of each node from the graph (root's parent will be printed as '?') */
void print_parents(Vertex **graph) {
    for (int j = 0; j < ARRAY_SIZE; ++j) {
        Vertex *node = *(graph + j);
        printf("The parent of node %c is node %c\n", node->value, node->parent);
    }
}