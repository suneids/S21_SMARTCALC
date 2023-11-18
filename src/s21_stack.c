#include "s21_stack.h"
#include <stdlib.h>

int s21_push(stack **root, stack_item value){
    int result = SUCCESS;
    stack *adding_elem = (stack*)malloc(sizeof(stack));
    if(adding_elem != NULL){
        adding_elem->next = *root;
        adding_elem->value = value;
        *root = adding_elem;
    }
    else{
        result = FAIL;
    }
    return result;
}


stack s21_pop(stack **root){
    stack result = {NULL, {0, "\0", -2}};
    if(*root != NULL){
        result = **root;
        stack *next = (*root)->next;
        free(*root);
        *root = next;
        result.next = NULL;
    }
    return result;
}


int s21_top(stack *root, stack_item *value){
    int result = SUCCESS;
    stack_item temp_item = {0, "\0", -1}; 
    *value = temp_item;
    if(root!=NULL){ 
        temp_item = root->value;
    }
    else{
        result = FAIL;
    }
    if(value != NULL)
        *value = temp_item;
    return result;
}

int s21_sizeof_stack(stack *root){
    int result = 0;
    stack *temp = root;
    while(temp!=NULL){
        result++;
        temp = temp->next;
    }
    return result;
}

void s21_destroy_stack(stack *root){
    if(root!=NULL){
        while((root != NULL) && (root->next!=NULL)){
            stack *temp = root;
            root = root->next;
            free(temp);
        }
        free(root);    
    }
}
