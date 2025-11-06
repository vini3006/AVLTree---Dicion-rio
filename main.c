#include <stdio.h>
#include "tree.h"

int main (){
    // Main switch

    /*
    int x = 0;
    while (x != 6) {

        scanf("%d", &x);
        switch (x) {
            case 1:
                
                createTree();
            case 2:
                // function 2. remove a word
            case 3: 
                // function 3. insert a word
            case 4: 
                // function 4. search a word
            case 5:
                // function 5. print the avlTree
        }
    }
    */
    AvlTree * dictionary = createTree();
    insertWord("casa", "local para morar", dictionary);
    insertWord("dedo", "parte do corpo", dictionary);
    insertWord("escada", "lugar pra subir", dictionary);
    printf("%s\n", dictionary->root->word);
    printf("%s\n", dictionary->root->left->word);
    printf("%s\n", dictionary->root->right->word);
    searchWord("escada", dictionary, 1);
    return 0;
}
