#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"


/* Create new Node* */
Node_tree* newNode(int data) {
    Node_tree *p = (Node_tree*) malloc (sizeof(Node_tree));
    p->data = data;
    p->ls = p->rs = NULL;
    return p;
}


/* Create new Node* from integer input, and insertion it to a given tree */
void insert(Node_tree **root, int data) {
    Node_tree* q = *root;
    if (q == NULL) {
        *root = newNode(data);
        return;
    }
    if (data <= q->data)
        insert(&q->ls, data);    
    else
        insert(&q->rs, data);
}


/* Checking (recursively) the height of the tree (the longest branch) */
int treeHeight(Node_tree *root) {
    Node_tree* q = root;
    if (q == NULL)
        return 0;
    else {
        int left = treeHeight(q->ls);
        int right = treeHeight(q->rs);
        if (left > right)
            return 1 + left;
        else
            return 1 + right;
    }
}


/* Count the amount of the Nodes in the tree */
int numOfNodes(Node_tree *root) {
    Node_tree* q = root;
    if (q == NULL)
        return 0;
    else return 1 + numOfNodes(q->ls) + numOfNodes(q->rs);
}


/* Printing the values of all the elements in the tree */
void printTree(Node_tree *root) {
    if (root == NULL)
        return;
    else {
        Node_tree* q = root;
        printTree(q->rs);
        printTreeRec(q);
        printTree(q->ls);
    }
}


/* Printing the value of a spacific Node */
void printTreeRec(Node_tree *root) {
    printf("The data is: ");
    printf("%d\n", root->data);
    return;
}


/* Checking if a number is in the tree */
int isIn(Node_tree *root, int data) {
    Node_tree* q = root;
    if (q == NULL)
        return 0;
    if (data == q->data)
        return 1;
    else {
        if (data > q->data)
           return isIn(q->rs, data); 
        else
            return isIn(q->ls, data);
    }
}


/* Clean the tree (and free the memory allocation) */
void freeTree(Node_tree *root) {
    if (!root)
        return;
    
    freeTree(root->ls);
    freeTree(root->rs);
    
    free(root);
}




