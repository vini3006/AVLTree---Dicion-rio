#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

// Cria um novo nó

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

// Cria uma nova árvore

AvlTree * createDictionary() {
    AvlTree * newTree = malloc(sizeof(AvlTree));
    newTree -> root = NULL;
    return newTree;
}

// Verifica se a árvore está vazia

int emptyTree(AvlTree * Tree){
   Tree->root == NULL ? 1 : 0;
}

// Rotações

void LL(AvlTree * T, Node * n){
    Node * aux = n->right;

    // Rotação em si 
    n->right = aux->left;
    aux->left = n;

    // Atualiza os ponteiros dos pais e da raiz, caso necessário
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

    // Atualiza os fatores de balanceamento
    if(aux->BF == -1){
        n->BF = 0;
        aux->BF = 0;
    }
    else if (aux->BF == 0) {
        n->BF = -1;
        aux->BF = 1;
    }
}

void RR(AvlTree * Tree, Node * n){
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
        Tree->root = aux;
    }

    aux->father = n->father;
    n->father = aux;
    if (n->left != NULL) n->left->father = n;

    if(aux->BF == 1){
        n->BF = 0;
        aux->BF = 0;
    }
    else if (aux->BF == 0) {
        n->BF = 1;
        aux->BF = -1;
    }
}

void LR(AvlTree * Tree, Node * n){
    LL(Tree, n->left);
    RR(Tree, n);
}

void RL(AvlTree * Tree, Node * n){
    RR(Tree, n->right);
    LL(Tree, n);
}

void balance(AvlTree * Tree, Node * n){
    if(n == NULL) return; // condição de parada da recursão

    Node * father = n->father; // guarda o pai para a proxima chamada para evitar chamadas desnecessárias caso haja rotação

    if(n->BF == 2){
        if(n->left->BF == -1){
            LR(Tree, n);
        } else {
            RR(Tree, n);
        }
    } 
    else if (n->BF == -2){
        if(n->right->BF == 1){
            RL(Tree, n);
        } else {
            LL(Tree, n);
        }
    }

    balance(Tree, father);
}

Node * RecursiveInsertion(Node * newWord, Node * currentNode) {
    if (currentNode == NULL){
        printf("Inserção de %s com sucesso.\n", newWord->word);
        return newWord;
    }

    int cmp = strcmp(newWord->word, currentNode->word);

    if (cmp == 0) { 
        printf("Operação de Inserção de %s sem sucesso. Palavra já existe no dicionário.\n", newWord->word);
        return currentNode;
    } 
    
    if (cmp < 0){
        currentNode->left = RecursiveInsertion(newWord, currentNode->left);
        if(currentNode->left != NULL) currentNode->left->father = currentNode;
        currentNode->BF++;
    } 
    else if (cmp > 0){
        currentNode->right = RecursiveInsertion(newWord, currentNode->right);
        if(currentNode->right != NULL) currentNode->right->father = currentNode;
        currentNode->BF--;
    }

    return currentNode;
}

void insert(char * word, char * meaning, AvlTree * Tree){
    if (Tree == NULL) {
        printf("Árvore não encontrada.\n");
        return; 
    }

    Node * newWord = createNode(word, meaning);
    Tree->root = RecursiveInsertion(newWord, Tree->root);
    if(newWord->father != NULL) {
        balance(Tree, newWord->father);
    }
}