typedef struct avl* AVL;

int height(AVL a);
int getBalance(AVL N);
AVL insert(AVL node, char* code);
void preOrder(AVL root);
int search(AVL root,char* key);
char* getCode(AVL a);
AVL getLeft(AVL a);
AVL getRight(AVL a);