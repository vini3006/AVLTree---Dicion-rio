#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

Node * RecursiveInsertion(Node * newWord, Node * currentNode);

void insertTree(char * word, char * meaning, AvlTree * Tree);