#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "LinkedList.h"
  
struct Node{
    char* produto;
    float data; 
    struct Node* next; 
};
  

struct Node* SortedMerge(Lligada a, Lligada b); 
void FrontBackSplit(Lligada source, Lligada* frontRef, Lligada* backRef); 

float getData(Lligada a){
    return a->data;
}
char* getLinha(Lligada a){
    return a->produto;
}
void getValor_Produto(Lligada a,char** line){

    sprintf(*line,"%f ",a->data);
    strcat(*line,a->produto);
}

Lligada getNext(Lligada a){
    return a->next;
}

void MergeSort(Lligada* headRef){ 

    Lligada head = *headRef; 
    Lligada a; 
    Lligada b; 
  
    if ((head == NULL) || (head->next == NULL)){ 
        return; 
    } 

    FrontBackSplit(head, &a, &b);  

    MergeSort(&a); 
    MergeSort(&b); 
  
    *headRef = SortedMerge(a, b); 
} 

Lligada SortedMerge(Lligada a, Lligada b){ 

    Lligada result = NULL; 
  
    if(a == NULL) return b; 
    else if(b == NULL) return a;

    if(a->data >= b->data){ 
        result = a; 
        result->next = SortedMerge(a->next, b); 
    } 
    else{ 
        result = b; 
        result->next = SortedMerge(a, b->next); 
    } 
    return(result); 
} 

void FrontBackSplit(Lligada source, Lligada* frontRef, Lligada* backRef){ 

    Lligada fast; 
    Lligada slow; 
    slow = source; 
    fast = source->next; 
  
    
    while (fast != NULL){ 
        fast = fast->next; 
        if (fast != NULL){ 
            slow = slow->next; 
            fast = fast->next; 
        } 
    } 
  
    *frontRef = source; 
    *backRef = slow->next; 
    slow->next = NULL; 
} 
  
void printList(Lligada node){ 

    while(node != NULL){ 
        printf("%f %s\n",node->data,node->produto);
        node = node->next; 
    } 
}

float getKdata(Lligada a, int k){
    Lligada *temp = &a;
    int count = 0;
    while(*temp && count < k){
        count++;
        temp = &((*temp)->next);
    }
    return (*temp)->data;
}

float maxLligada(Lligada a, int k){
    float max = 0;
    Lligada *temp = &a;

    int count = 0;
    while(*temp && count < k){
        count++;
        temp = &((*temp)->next);
    }

    while(*temp){
        if((*temp)->data > max) max = (*temp)->data;
        temp = &((*temp)->next);
    }
    return max;
}

void push(Lligada* head_ref, float new_data, char* produto){ 

    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
    int found = 0;
    Lligada pt = *head_ref;
    while(pt && !found){
        if(!strcmp(pt->produto,produto)){
            pt->data += new_data;
            found = 1;
        }
        pt = pt->next;
    }
    if(!found){
        new_node->data = new_data; 
        new_node->produto = strdup(produto);
        new_node->next = (*head_ref);  
        (*head_ref) = new_node; 
    }
}  

int sizeLligada(Lligada a){
    Lligada *temp = &a;
    int count = 0;
    while(*temp){
        count++;
        temp =&((*temp)->next);
    }
    return count;
}