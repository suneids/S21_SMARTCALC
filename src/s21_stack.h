#ifndef S21_STACK_H
#define S21_STACK_H
#define SUCCESS 0
#define FAIL 1

typedef struct s21_stack_item{
    long double number;
    char oper[5];
    int prio;
}stack_item;
 
typedef struct s21_stack{
    struct s21_stack *next;
    stack_item value;
}stack;

int s21_push(stack **root, stack_item value);
stack s21_pop(stack **root);
int s21_top(stack *root, stack_item *value);
int s21_sizeof_stack(stack *root);
void s21_destroy_stack(stack *root);
#endif // S21_STACK_H
