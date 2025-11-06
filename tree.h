#ifndef TREE
#define TREE

typedef struct node {
    char * word;
    char * meaning;
    struct node * left;
    struct node * right;
    struct node * father;
    int BF;
} Node;

typedef struct avltree {
    Node * root;
} AvlTree; 

Node * createNode(char * word, char * meaning);

AvlTree * createTree();

int emptyTree(AvlTree * Tree);

void LL(AvlTree * T, Node * n);

void RR(AvlTree * T, Node * n);

void LR(AvlTree * T, Node * n);

void RL(AvlTree * T, Node * n);

Node * RecursiveInsertion(Node * newWord, Node * currentNode);

void insertTree(char * word, char * meaning, AvlTree * Tree);

#endif