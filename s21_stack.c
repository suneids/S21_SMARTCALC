#include "s21_stack.h"
#include <stdlib.h>

int s21_push(stack **root, stack_item value){
    int result = SUCCES;
    stack *temp, *adding_elem = (stack*)malloc(sizeof(stack));
    adding_elem->next =NULL;
    stack_item zero_item = {0, "\0", -1};
    adding_elem->value = zero_item;
    if(adding_elem != NULL){
        adding_elem->value = value;
        if(*root == NULL)
            *root = adding_elem;
        else{
            temp = *root;
            while(temp->next != NULL) temp = temp->next;
            temp->next = adding_elem;
        }
    }
    else
        result = FAIL;
    return result;
}


stack* s21_pop(stack *root){
    stack* result = NULL;
    if(root != NULL){
        stack* prelast = NULL;
        result = root;
        while(result->next != NULL){
            prelast = result;
            result = result->next;
        }
        if(prelast != NULL)
            prelast->next = NULL;
    }
    return result;
}


int s21_top(stack *root, stack_item *value){
    int result = SUCCES;
    stack_item temp_item = {0, "\0", -1}; 
    if(root!=NULL){ 
        stack *temp = root;
        while(temp->next != NULL)
            temp = temp->next;
        temp_item = temp->value;
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
    if(root != NULL){
        while(root->next!=NULL){
            stack *temp = root->next;
            free(root);
            root = temp;
        }
        free(root);
    }
}
