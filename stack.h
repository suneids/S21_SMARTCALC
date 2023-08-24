#ifndef STACK_H
#define STACK_H
typedef struct stack{
    struct stack *next;
    double value;
    char oper;
}stack;

int push(stack *root, double value, char oper);
stack* pop(stack *root);
int top(stack *root, double *value, char *oper);
void destroy(stack *root);
#endif // STACK_H
