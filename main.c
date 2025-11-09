#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#define MAX_WORDSIZE 2048
#define MAX_MEANINGSIZE 2048

// Remove a quebra de linha da string lida pelo fgets
void removeNewLine(char * word){
    size_t len = strlen(word);
    if (len > 0 && word[len - 1] == '\n') {
        word[len - 1] = '\0';
    }
}

void flush_buffer(){
    int c;
    while ((c = fgetc(stdin)) != '\n' && c != EOF);
}

int main (){ 

    int x = 0;
    AvlTree * dictionary = NULL;
    
    while (x != 6) {

        if(scanf("%d", &x) != 1) {
            break;
        }

        flush_buffer();
        
        switch (x) {
            case 1:{
                dictionary = createTree();
                break;
            }
            case 2: {
                char word[MAX_WORDSIZE];

                if (dictionary == NULL) break;

                fgets (word, MAX_WORDSIZE, stdin);
                removeNewLine(word);

                removeWord(word, dictionary);
                break;
            }
            case 3: {
                char word[MAX_WORDSIZE];
                char meaning[MAX_MEANINGSIZE];
                
                if (dictionary == NULL) break;

                fgets (word, MAX_WORDSIZE, stdin);
                removeNewLine(word);
                fgets (meaning, MAX_MEANINGSIZE, stdin);
                removeNewLine(meaning);

                insertWord(word, meaning, dictionary);
                break;
            }
            case 4: {
                char word[MAX_WORDSIZE];

                if (dictionary == NULL) break;

                fgets (word, MAX_WORDSIZE, stdin);
                removeNewLine(word);

                searchWord(word, dictionary, 1);
                break;
            }
            case 5: {
                if(dictionary == NULL) break;
                printTree(dictionary);
                break;
            }
        }
    }

    freeTree(dictionary);
    
    return 0;
}
