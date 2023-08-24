#include "stack.h"
#include <stdlib.h>

int push(stack *root, double value, char oper){
    int result = 0;
    stack *temp, *adding_elem = (stack*)malloc(sizeof(stack));
    if(adding_elem != NULL){
        adding_elem->oper = oper;
        adding_elem->value = value;
        adding_elem->next = NULL;
        if(root == NULL)
            root = adding_elem;
        else{
            temp = root;
            while(temp->next != NULL) temp = temp->next;
            temp->next = adding_elem;
        }
    }
    else
        result = 1;
    return result;
}


stack* pop(stack *root){
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


int top(stack *root, double *value, char *oper){
    int result = 0;
    if(root!=NULL){
        stack *temp = root;
        while(temp->next != NULL) temp = temp->next;
        *value = temp->value;
        *oper = temp->oper;
    }
    else{
        result = 1;
    }
    return result;
}


void destroy(stack *root){
    if(root != NULL){
        while(root->next!=NULL){
            stack *temp = root->next;
            free(root);
            root = temp;
        }
        free(root);
    }
}
