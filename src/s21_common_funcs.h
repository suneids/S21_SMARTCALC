#ifndef S21_COMMON_FUNCS_H
#define S21_COMMON_FUNCS_H
int s21_is_oper(char *lexem);
int s21_is_func(char *lexem);
int s21_is_oper_or_func(char *lexem);
int s21_is_digit(char symbol);
int s21_is_digit_or_point(char symbol);
int s21_is_parenthesis(char *lexem);
long double s21_round(long double x, int power);
#endif


