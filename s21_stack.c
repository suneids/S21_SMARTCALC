#include "s21_stack.h"
#include <stdlib.h>

int s21_push(stack **root, double value, char oper){
    int result = SUCCES;
    stack *temp, *adding_elem = (stack*)malloc(sizeof(stack));
    if(adding_elem != NULL){
        adding_elem->oper = oper;
        adding_elem->value = value;
        adding_elem->next = NULL;
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


int s21_top(stack *root, double *value, char *oper){
    int result = SUCCES;
    if(value != NULL)
        *value = 0;
    if(oper != NULL)
        *oper = '\0';
    if(root!=NULL){
        stack *temp = root;
        while(temp->next != NULL)
            temp = temp->next;
        if(value != NULL)
            *value = temp->value;
        if(oper != NULL)
            *oper = temp->oper;
    }
    else{
        result = FAIL;
    }
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
