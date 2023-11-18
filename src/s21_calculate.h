#ifndef S21_CALCULATE_H
#define S21_CALCULATE_H
#include "s21_stack.h"
long double s21_calculation(char *input, int in_rad, int *error);//последнее - числа в функциях указаны в радианах
int s21_intermediate_calculation(stack **nums, stack_item *current_oper, int in_rad, int *error);
void s21_write_by_value(stack **operators, stack **nums, char *lexem, int in_rad, int *error);
void s21_set_priority(stack_item *item, stack **operators);
int s21_lexem_to_num(stack_item *item, char *lexem);
int s21_exec_operation(long double num1, long double num2, char *current_oper, stack_item *after_calculation, int *error);
int s21_exec_func(long double num2, char *current_oper, stack_item *after_calculation, int in_rad, int *error);
long double s21_grad_to_rad(long double grad);
long double s21_rad_to_grad(long double rad);
#endif
