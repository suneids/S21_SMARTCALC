#ifndef S21_CALCULATE_H
#define S21_CALCULATE_H
long double s21_calculate(char *input_string);
int s21_write_by_value(stack_item *new_item, char *lexem);
void s21_set_priority(char *lexem, stack_item *item);
int s21_lexem_to_num(stack_item *item, char *lexem);
int s21_is_digit(char symbol);
#endif