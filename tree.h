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

int emptyTree(AvlTree * Tree);

int height(Node * n);

void LL(AvlTree * T, Node * n);

void RR(AvlTree * T, Node * n);

void LR(AvlTree * T, Node * n);

void RL(AvlTree * T, Node * n);

void balance(AvlTree * Tree, Node * n);

Node * RecursiveInsertion(Node * newWord, Node * currentNode);

void insertWord(char * word, char * meaning, AvlTree * Tree);

Node * searchWord(char * word, AvlTree * T, int print);

Node * predecessor(Node * n);

void removeWord(char * word, AvlTree * Tree);

#endif