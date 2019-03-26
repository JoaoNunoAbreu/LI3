#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct avl{
    char* code;
    struct avl *left,*right;
    int height;
}*AVL;

int height(AVL a);
int getBalance(AVL N);
AVL insert(AVL node, char* code);
void preOrder(AVL root);
int search(AVL root,char* key);