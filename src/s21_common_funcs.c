#include "s21_common_funcs.h"
#include "string.h"
#include <math.h>
int s21_is_oper(char *lexem) {
    int result = 0;
    char singles[] = "+-*/^()";
    for (int i = 0; i < (int)strlen(singles) && !result; i++) {
        if (lexem[0] == singles[i]) {
            result = 1;
        }
    }
    if(!result && !strncmp(lexem, "mod", 3)){
        result = 1;
    }
    return result;
}

int s21_is_oper_or_func(char *lexem) {
    int result = 0;
    if(lexem != NULL) 
        result = s21_is_oper(lexem);
    if(!result)
        result = s21_is_func(lexem);
    return result;
}

int s21_is_func(char *lexem){
    int result = 0;
    const int funcs_count = 9;
    char funcs[][5] = {"cos", "sin", "tan", "acos", "asin", "atan", "sqrt", "ln", "log"};
    for (int i = 0;  lexem != NULL && (i < funcs_count) && !result; i++) {
        if (!strcmp(lexem, funcs[i])) {
            result = 1;
        }
    }
    return result;
}

int s21_is_digit(char symbol){
    return (symbol <= '9') && (symbol >= '0');
}

int s21_is_digit_or_point(char symbol){
    return s21_is_digit(symbol) || (symbol == '.');
}

int s21_is_parenthesis(char *lexem){
    int result = !strcmp(lexem, "(");
    if(!strcmp(lexem, ")")){
        result = -1;
    }
    return result;
}


long double s21_round(long double x, int power){
    long double result = round(x);
    x -= result;
    x *= pow(10, power);
    x = round(x);
    result += x*pow(10, -power);
    return result;
}
