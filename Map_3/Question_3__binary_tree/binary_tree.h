

typedef struct Node_tree {
    int data;
    struct Node_tree *ls, *rs;
} Node_tree;



Node_tree* newNode(int data);
void insert(Node_tree **root, int data);
int treeHeight(Node_tree *root);
int numOfNodes(Node_tree *root);
void printTreeRec(Node_tree *root);
void printTree(Node_tree *root);
void freeTree(Node_tree *root);
int isIn(Node_tree *root, int data);
