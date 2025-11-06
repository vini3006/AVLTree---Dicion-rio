#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

Node * createNode(char * word, char * meaning){
    Node * newNode = malloc(sizeof(Node));
    newNode->word = word;
    newNode->meaning = meaning;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->father = NULL;
    newNode->BF = 0;
    return newNode;
}

AvlTree * createTree() {
    AvlTree * newTree = malloc(sizeof(AvlTree));
    newTree -> root = NULL;
    return newTree;
}

int emptyTree(AvlTree * Tree){
   Tree->root == NULL ? 1 : 0;
}

void LL(AvlTree * T, Node * n){
    Node * aux = n->right;

    n->right = aux->left;
    aux->left = n;

    if (n->father != NULL){
        if (n == n->father->right){
            n->father->right = aux;
        } else {
            n->father->left = aux;
        }
    } else {
        T->root = aux;
    }
    
    aux->father = n->father;
    n->father = aux;
    if (n->right != NULL) n->right->father = n;
}

void RR(AvlTree * T, Node * n){
    Node * aux = n->left;

    n->left = aux->right;
    aux->right = n;

    if (n->father != NULL){
        if (n == n->father->right){
            n->father->right = aux;
        } else {
            n->father->left = aux;
        }
    } else {
        T->root = aux;
    }

    aux->father = n->father;
    n->father = aux;
    if (n->left != NULL) n->left->father = n;
}

void LR(AvlTree * T, Node * n){
    Node * aux = n->left;
    LL(T, aux);
    RR(T, n);
}

void RL(AvlTree * T, Node * n){
    Node * aux = n->right;
    RR(T, aux);
    LL(T, n);
}

Node * RecursiveInsertion(Node * newWord, Node * currentNode) {
    if (currentNode == NULL){
        return newWord;
    }

    if (strcmp(newWord->word, currentNode->word) == 0) { 
        printf("Operação de Inserção de casa sem sucesso. Palavra já existe no dicionário.\n");
        return currentNode;
    }

    if (strcmp(newWord->word, currentNode->word) < 0){
        currentNode->left = RecursiveInsertion(newWord, currentNode->left);
    }

    if (strcmp(newWord->word, currentNode->word) > 0){
        currentNode->right = RecursiveInsertion(newWord, currentNode->right );
    }

    return currentNode;
}

void insertTree(char * word, char * meaning, AvlTree * Tree){
    if (Tree == NULL) {
        printf("Árvore não encontrada.\n");
        return; 
    }

    Node * newWord = createNode(word, meaning);
    Tree->root = RecursiveInsertion(newWord, Tree->root);
    printf("Inserção de casa com sucesso.\n");
}