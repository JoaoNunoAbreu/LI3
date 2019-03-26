#include "AVL.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct avl{
    char* code;
    struct avl *left,*right;
    int height;
};

int height(AVL a){ 
    if(a == NULL) return 0; 
    return a -> height; 
}
int max(int a, int b){ 
    return (a > b)? a : b; 
}
AVL newNode(char* code){

    AVL a = (AVL) malloc(sizeof(struct avl));
    a -> code = strdup(code);
    a -> left = NULL; 
    a -> right = NULL; 
    a -> height = 1;
    return a;
}
AVL rightRotate(AVL y){ 
    
    AVL x = y -> left; 
    AVL T2 = x -> right; 
    x->right = y; 
    y->left = T2; 
    y->height = max(height(y->left), height(y->right))+1; 
    x->height = max(height(x->left), height(x->right))+1; 
    return x; 
}
AVL leftRotate(AVL x){ 

    AVL y = x -> right; 
    AVL T2 = y -> left; 
    y -> left = x; 
    x -> right = T2; 
    x -> height = max(height(x->left), height(x->right))+1; 
    y -> height = max(height(y->left), height(y->right))+1; 
    return y; 
} 
int getBalance(AVL N){ 
    if (N == NULL) return 0; 
    return height(N->left) - height(N->right); 
} 
AVL insert(AVL node, char* code){ 

    if (node == NULL) return(newNode(code));
  
    if (strcmp(code,node->code) < 0) node -> left  = insert(node->left,code); 
    else if (strcmp(code,node -> code) > 0) node->right = insert(node->right,code); 
    else return node; 
  
    node -> height = 1 + max(height(node->left),height(node->right)); 

    int balance = getBalance(node); 
  
    /* Left Left Case */
    if (balance > 1 && strcmp(code,node->left->code) < 0) return rightRotate(node); 
  
    /* Right Right Case */
    if (balance < -1 && strcmp(code,node->right->code) > 0) return leftRotate(node); 
  
    /* Left Right Case */
    if (balance > 1 && strcmp(code,node->left->code) > 0){ 
        node->left = leftRotate(node->left); 
        return rightRotate(node); 
    } 
    /* Right Left Case */
    if (balance < -1 && strcmp(code,node->right->code) < 0){ 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 
    return node; 
}
void preOrder(AVL root){ 
    if(root != NULL){ 
        printf("%s\n",root->code); 
        preOrder(root->left); 
        preOrder(root->right); 
    } 
}
int search(AVL root,char* key){

    if(root == NULL) return 0;
    if(strcmp(key,root->code) < 0) return search(root->left,key);
    else if(strcmp(key,root->code) > 0) return search(root->right,key);
    else return 1;
}

char* getCode(AVL a){
    return strdup(a->code);
}

AVL getLeft(AVL a){
    if(a == NULL) return NULL;
    return a->left;
}

AVL getRight(AVL a){
    if(a == NULL) return NULL;
    return a->right;
}