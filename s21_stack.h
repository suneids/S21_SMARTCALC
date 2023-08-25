#ifndef S21_STACK_H
#define S21_STACK_H
#define SUCCES 0
#define FAIL 1

typedef struct stack{
    struct stack *next;
    double value;
    char oper;
}stack;

int s21_push(stack **root, double value, char oper);
stack* s21_pop(stack *root);
int s21_top(stack *root, double *value, char *oper);
int s21_sizeof_stack(stack *root);
void s21_destroy_stack(stack *root);
#endif // S21_STACK_H
