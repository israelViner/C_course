#include <stdio.h>
#include <stddef.h>
#include "binary_tree.h"


int main() {
    
    /* Create the tree and insert the element from an array to the tree */
    int array[] = {5,3,8,1,4,9};
    int N = sizeof(array)/sizeof(int);
    Node_tree *root = NULL;
    int i;
    for(i=0; i<N; ++i)
        insert(&root,array[i]);
    
    /* Checking the 6 functions of the tree */
    printTree(root);
    for(i=1; i<=10; ++i)
        if(isIn(root,i))
            printf("%d is in the tree.\n",i);
    printf("Tree Height: %d\n", treeHeight(root));
    printf("Number of nodes: %d \n", numOfNodes(root));
    freeTree(root);
    //printTree(root);
    
    return 0;

}