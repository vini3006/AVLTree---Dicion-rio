#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

// Cria um novo nó

Node * createNode(char * word, char * meaning){
    Node * newNode = malloc(sizeof(Node));
    if(newNode == NULL) return NULL;

    newNode->word = strdup(word);
    newNode->meaning = strdup(meaning);
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->father = NULL;
    newNode->BF = 0;
    return newNode;
}

// Cria uma nova árvore

AvlTree * createTree() {    
    AvlTree * newTree = malloc(sizeof(AvlTree));
    newTree -> root = NULL;
    printf("Árvore criada com sucesso!\n");
    return newTree;
}

// Verifica se a árvore está vazia

int emptyTree(AvlTree * Tree){
   Tree->root == NULL ? 1 : 0;
}

// Calcula a altura do nó 
int height(AvlTree* Tree, Node * n){
    Node * aux = Tree->root;
    int h = 1;

       while (aux != NULL){
        int cmp = strcmp (n->word, aux->word);
        
        if(cmp == 0) break;

        if(cmp < 0){
            aux = aux->left;
        } else {
            aux = aux->right;
        }
        h++;
    }
    return h;
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

    if(n->father != NULL) balance(Tree, father);
}  

// Faz a inserção recursivamente atualizando os FBs e retorna um ponteiro pro nó raiz ao final
Node * RecursiveInsertion(AvlTree * Tree, Node * newWord, Node * currentNode, int * height_changed) {
    if (currentNode == NULL){   
        * height_changed = 1;
        printf("\nInserção de %s com sucesso.\n", newWord->word);
        return newWord;
    }

    int cmp = strcmp(newWord->word, currentNode->word);

    if (cmp == 0) { 
        * height_changed = 0;
        printf("\nOperação de Inserção de %s sem sucesso. Palavra já existe no dicionário.\n", newWord->word);
        return currentNode;
    } 
    
    if (cmp < 0){
        currentNode->left = RecursiveInsertion(Tree, newWord, currentNode->left, height_changed);
        if(currentNode->left != NULL) currentNode->left->father = currentNode;

        if(* height_changed == 1)currentNode->BF++;

        if(currentNode->BF == 0) * height_changed = 0;

        else if(currentNode->BF == 2){
            if(currentNode->left->BF == -1){
                LR(Tree, currentNode);
            } else {
                RR(Tree, currentNode);
            }

            * height_changed = 0;

            return currentNode->father;
        }
    } 
    else if (cmp > 0){
        currentNode->right = RecursiveInsertion(Tree, newWord, currentNode->right, height_changed);
        if(currentNode->right != NULL) currentNode->right->father = currentNode;

        if(* height_changed == 1) currentNode->BF--;

        if(currentNode->BF == 0) * height_changed = 0;

        else if(currentNode->BF == -2){
            if(currentNode->right->BF == 1){
                RL(Tree, currentNode);
            } else {
                LL(Tree, currentNode);
            }

            * height_changed = 0;

            return currentNode->father;
        }
    }

    return currentNode;
}

// Faz a chamada da inserção recursiva e rebalancea a árvore
void insertWord(char * word, char * meaning, AvlTree * Tree){
    if (Tree == NULL) {
        printf("\nÁrvore não encontrada.\n");
        return; 
    }

    Node * newWord = createNode(word, meaning);

    int height_changed = 0;

    Tree->root = RecursiveInsertion(Tree, newWord, Tree->root, &height_changed);
}

// Realiza a busca de uma palavra e retorna o nó que guarda a mesma (caso exista)
Node * searchWord(char * word, AvlTree * T, int print){
    if (T == NULL){
        if(print) printf("\nÁrvore não encontrada!\n");
        return NULL;
    }

    Node * searcher = T->root;

    while (searcher != NULL){
        int cmp = strcmp (word, searcher->word);
        
        if(cmp == 0) break;

        if(cmp < 0){
            searcher = searcher->left;
        } else {
            searcher = searcher->right;
        }
    }

    if (searcher == NULL){
        if(print) printf("\nBusca sem sucesso!\n");
    } else {
        if(print) printf("\n%s está no dicionário (Altura = %d)\n%s\n", searcher->word, height(T, searcher), searcher->meaning);
    }

    return searcher;
}

// Encontra o antecessor para fazer as remoções quando necessário
Node * predecessor(Node * n){
    if (n->left == NULL) return NULL;

    n = n->left;
    while (n->right != NULL){
        n = n->right;
    }

    return n;
}

// Remove o nó da árvore 
void removeWord(char * word, AvlTree * Tree){
    Node * aux = searchWord(word, Tree, 0);
    if (aux == NULL){
        printf("\nOperação de remoção inválida!\n");
        return;
    }

    Node * father = aux->father;

    // Caso em que o nó é uma folha
    if (aux->left == NULL && aux->right == NULL){
        if (aux->father != NULL){
            if (aux == aux->father->left){
                aux->father->left = NULL;
                aux->father->BF--;
            } else {
                aux->father->right = NULL;
                aux->father->BF++;
            }
        } else {
            Tree->root = NULL;
        }

        aux->left = aux->right = aux->father = NULL;
        free(aux);
    }
    //Caso em que o nó possui apenas um dos filhos
    else if (aux->left == NULL || aux->right == NULL){
        Node * child = (aux->left != NULL) ? aux->left : aux->right;

        if (child != NULL){
            child->father = aux->father;
        }
        if (aux->father != NULL){
            if (aux == aux->father->left){
                aux->father->left = child;
                aux->father->BF--;
            } else {
                aux->father->right = child;
                aux->father->BF++;
            }
        } else {
            Tree->root = child;
        }

        aux->left = aux->right = aux->father = NULL;
        free(aux);
    }
    //Caso em que o nó possui os 2 filhos 
    else {
        Node * pred = predecessor(aux);
        char * predWord = strdup(pred->word);
        char * predMeaning = strdup(pred->meaning);

        removeWord(pred->word, Tree);

        strcpy(aux->word, predWord);
        strcpy(aux->meaning, predMeaning);

        free(predWord);
        free(predMeaning);
    }

    if(father != NULL) balance(Tree, father);
}

void inOrderPrint(AvlTree * Tree, Node * n){
    if (n == NULL) return;

    inOrderPrint(Tree, n->left);
    printf("%s (Altura = %d) ", n->word, height(Tree, n));
    inOrderPrint(Tree, n->right);
}

void printTree(AvlTree * Tree){
    printf("\nDicionário: ");
    inOrderPrint(Tree, Tree->root);
    printf("\n");
}

