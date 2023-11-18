#include "s21_validator.h"
#include "s21_common_funcs.h"
#include <string.h>

int s21_calculation_possible(char *input_str)
{
    int result = 0;
    if(s21_count_symbols(input_str, "(") != s21_count_symbols(input_str, ")")){}

    else{
        result = 1;
    }
    return result;
}

int s21_add_possible(char *input_str, char *key)
{
    int result = 0;
    char kf_symbol = key[0];
    if(s21_is_oper(key)){
        if(s21_can_add_operator(input_str, key))
            result = 1;
    }
    else if(s21_is_func(key)){
        if(s21_can_add_function(input_str))
            result = 1;
    }
    else if(s21_is_digit(kf_symbol) || kf_symbol == 'x'){
        if(s21_can_add_digit(input_str, key))
            result = 1;
    }
    return result;
}

int s21_can_add_operator(char *input_str, char *oper){
    int result = 0;
    char kf_symbol = oper[0];
    char last_symbol = input_str[strlen(input_str)-1];
    if((s21_count_symbols(input_str, "(") == s21_count_symbols(input_str, ")")) && (kf_symbol == ')')){
    }
    else if((strlen(input_str) == 0) && (s21_count_symbols("(-", &kf_symbol) == 0)){
    }
    else if(s21_is_oper(&last_symbol) && (s21_count_symbols("()", &kf_symbol) == 0)){
        if(s21_count_symbols("()", &last_symbol) > 0){
            result = 1;
        }
    }
    else if(kf_symbol == '(' && !s21_is_oper(&last_symbol) ){
    }
    else if(kf_symbol == ')' && !s21_is_digit(last_symbol) && s21_count_symbols(")x", &kf_symbol) == 0){
    }
    else{
        result = 1;
    }
    return result;
}

int s21_can_add_function(char *input_str){
    int result = 0;
    char last_symbol = input_str[strlen(input_str)-1];
    if(s21_is_digit(last_symbol)){

    }
    else{
        result = 1;
    }
    return result;
}

int s21_can_add_digit(char *input_str, char *digit){
    int result = 0;
    char kf_symbol = digit[0];
    char last_symbol = input_str[strlen(input_str)-1];
    if((s21_is_digit(last_symbol) || last_symbol == 'x') && kf_symbol == 'x'){
    }
    else if(last_symbol == ')'){
    }
    else{
        result = 1;
    }
    return result;
}

int s21_count_symbols(char *str, char *substr){
    int result = 0;
    char *temp = str;
    while(strstr(temp, substr)!=NULL){
        result++;
        temp = strstr(temp, substr);
        if(temp!=NULL)
            temp++;
    }
    return result;
}
