#ifndef S21_VALIDATOR_H
#define S21_VALIDATOR_H

int s21_calculation_possible(char *input_str);
int s21_add_possible(char *input_str, char *key);
int s21_can_add_operator(char *input_str, char *oper);
int s21_can_add_function(char *input_str);
int s21_can_add_digit(char *input_str, char *key);

int s21_count_symbols(char *str, char *substr);
#endif // S21_VALIDATOR_H
