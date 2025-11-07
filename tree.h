#ifndef TREE
#define TREE

typedef struct node {
    char * word;
    char * meaning;
    struct node * left;
    struct node * right;
    struct node * father;
    int BF; // balance factor
} Node;

typedef struct avltree {
    Node * root;
} AvlTree; 

Node * createNode(char * word, char * meaning);

AvlTree * createTree();

int emptyTree(AvlTree * T);

int height(AvlTree * T, Node * n);

void LL(AvlTree * T, Node * n);

void RR(AvlTree * T, Node * n);

void LR(AvlTree * T, Node * n);

void RL(AvlTree * T, Node * n);

void balance(AvlTree * T, Node * n);

Node * RecursiveInsertion(AvlTree * T, Node * newWord, Node * currentNode, int * height_changed);

void insertWord(char * word, char * meaning, AvlTree * T);

Node * searchWord(char * word, AvlTree * T, int print);

Node * predecessor(Node * n);

void removeWord(char * word, AvlTree * T);

void inOrderPrint(AvlTree * T, Node * n);

void printTree(AvlTree * T);

#endif