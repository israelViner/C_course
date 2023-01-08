#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "BFS.h"

int main() {

    /* Create the graph - first the vertices (6 vertices), then link between some of them,
     and finally insert the vertices to the graph */

    /* Initialize an array of Vertices for the graph */
    graph = (Vertex**)malloc(sizeof(Vertex*) * ARRAY_SIZE);
    
   	/* Seed the random number generator */
    srand(time(NULL));
    
    /* Initialize the vertices for the graph */
    Vertex node_A = create_Vertex('A');
    Vertex node_B = create_Vertex('B');
    Vertex node_C = create_Vertex('C');
    Vertex node_D = create_Vertex('D');
    Vertex node_E = create_Vertex('E');
    Vertex node_F = create_Vertex('F');
    
    /* Insert the vertices into the graph */
    *graph = &node_A;
    *(graph + 1) = &node_B;
    *(graph + 2) = &node_C;
    *(graph + 3) = &node_D;
    *(graph + 4) = &node_E; 
    *(graph + 5) = &node_F;      
 
    /* Fill the arrays of the neighbors of each node */
    determining_neighborhoods(graph, &node_A);
    determining_neighborhoods(graph, &node_B);
    determining_neighborhoods(graph, &node_C);
    determining_neighborhoods(graph, &node_D);
    determining_neighborhoods(graph, &node_E);
    determining_neighborhoods(graph, &node_F);

    /* Print the graph with the list of the neighbors of each node */
    printf("\nThe graph is:\n");    
    print_graph(graph);
    printf("\n\n*****\n\n");
    
    /* Call to the scan function */
    bfs_scan(graph);

    /* Print the nodes with their parents after the scan (root's parent will be printed as '?') */
    printf("The result of the BFS scan is:\n\n");    
    print_parents(graph);

    free(node_A.neighbors_array);
    free(node_B.neighbors_array);
    free(node_C.neighbors_array);
    free(node_D.neighbors_array);
    free(node_E.neighbors_array);
    free(node_F.neighbors_array);

	return 0;
}