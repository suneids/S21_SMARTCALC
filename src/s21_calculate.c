#include "s21_calculate.h"
#include "s21_common_funcs.h"
#include "s21_lexem_parse.h"
#include "string.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#define PI 3.14159265358979323846

long double s21_calculation(char *input, int in_rad, int *error){
    int len = 0;
    char **lexems = s21_get_lexems(input, &len);
    long double result = 0;
    stack *operators = NULL, *nums = NULL;
    for(int i = 0; i < len && !*error; i++)
        s21_write_by_value(&operators, &nums, lexems[i], in_rad, error);
    if(!*error){
        do{
            stack_item current_oper = {0, "\0", 0};
            strcat(current_oper.oper, s21_pop(&operators).value.oper);
            if(strcmp(current_oper.oper, "\0")){
                s21_intermediate_calculation(&nums, &current_oper, in_rad, error);
            }
        }while(operators != NULL);
    }
    s21_destroy_lexems(lexems, len);
    s21_destroy_stack(operators);
    result = s21_pop(&nums).value.number;
    s21_destroy_stack(nums);
    return s21_round(result, 8);
}

int s21_intermediate_calculation(stack **nums, stack_item *current_oper, int in_rad, int *error){
    int result = 0;
    int calc_type = 0;
    if(s21_is_oper(current_oper->oper))
        calc_type = 1;
    else if(s21_is_func(current_oper->oper))
        calc_type = -1; 
    long double num2 = s21_pop(nums).value.number;
    stack_item after_calculation = {0, "\0", 0};
    if(calc_type == 1){
        if(current_oper->prio == 7){//Унарный минус
            after_calculation.number = -num2;
        }
        else{
            long double num1 = s21_pop(nums).value.number;
            s21_exec_operation(num1, num2, current_oper->oper, &after_calculation, error);
        }
    }
    else if(calc_type == -1){
        s21_exec_func(num2, current_oper->oper, &after_calculation, in_rad, error);
    }
    s21_push(nums, after_calculation);
    return result;
}

int s21_exec_operation(long double num1, long double num2, char *current_oper, stack_item *after_calculation, int *error){
    int result = 0, zero_division = num2 == 0;
    if(!strcmp(current_oper, "+"))
        num1+=num2;
    else if(!strcmp(current_oper, "-"))
        num1-=num2;
    else if(!strcmp(current_oper, "*"))
        num1*=num2;
    else if(!strcmp(current_oper, "/") && !zero_division)
        num1/=num2;
    else if(!strcmp(current_oper, "mod") && !zero_division)
        num1 = fmod(num1, num2);
    else
        *error = 1;
    after_calculation->number = num1;
    return result;
}

int s21_exec_func(long double num, char *current_oper, stack_item *after_calculation, int in_rad, int *error){
    int result = 0, greater0 = num > 0, badarc = (num < -1) || (num > 1), badtg = (fmod(num, 90) == 0) && (fmod(num, 180) != 0);
    if(!strcmp(current_oper, "sqrt") && greater0){
        after_calculation->number = sqrt(num);
    }
    else if(!strcmp(current_oper, "ln") && greater0){
        if(num > 0)
            after_calculation->number = log(num);
        else
            *error = 1;
    }
    else if(!strcmp(current_oper, "log") && greater0){
        if(num > 0)
            after_calculation->number = log10(num);
        else
            *error = 1;
    }
    else{
        long double arcgrads =  num;
        num = in_rad? num :  s21_grad_to_rad(num);
        if(!strcmp(current_oper, "sin")){
            after_calculation->number = sin(num);
        }
        else if(!strcmp(current_oper, "cos")){
            after_calculation->number = cos(num);
        }
        else if(!strcmp(current_oper, "tan") && !badtg){
            after_calculation->number = tan(num);
        }
        else if(!strcmp(current_oper, "asin") && !badarc){
            after_calculation->number = in_rad? asin(arcgrads) : s21_rad_to_grad(asin(arcgrads));
        }
        else if(!strcmp(current_oper, "acos") && !badarc){
            after_calculation->number = in_rad? acos(arcgrads) : s21_rad_to_grad(acos(arcgrads));
        }
        else if(!strcmp(current_oper, "atan")){
            after_calculation->number = in_rad? atan(arcgrads) : s21_rad_to_grad(atan(arcgrads));
        }
        else{
            *error = 1;
        }
    }
    return result;
}

void s21_write_by_value(stack **operators, stack **nums, char *lexem, int in_rad, int *error){
    static int betweenParenthesis = 0, operatorsBetweenParenthesis = 0;
    int parenthesis = s21_is_parenthesis(lexem);
    if(parenthesis == 1){
        betweenParenthesis = 1;
        stack_item parenthesis = {0, "(", 0};
        s21_push(operators, parenthesis);
    }
    stack_item temp =  {0, "\0", -1};
    if(!parenthesis && s21_is_oper_or_func(lexem)){// Создание элемента стэка как оператора
        strcat(temp.oper, lexem);
        s21_set_priority(&temp, operators);
        stack_item *last_oper = (stack_item*)malloc(sizeof(stack_item));
        s21_top(*operators, last_oper);
        while(last_oper->prio > -1 && last_oper->prio >= temp.prio && (betweenParenthesis <= (operatorsBetweenParenthesis > 1))){ //Если приоритет предыдущего оператора больше или равен приоритету текушего
            s21_top(*operators, last_oper);
            if(last_oper->prio > -1 && last_oper->prio >= temp.prio){
                *last_oper =  s21_pop(operators).value;
                s21_intermediate_calculation(nums, last_oper, in_rad, error);
                if(betweenParenthesis)
                    operatorsBetweenParenthesis--;
            }
        }
        s21_push(operators, temp);
        free(last_oper);
        if(betweenParenthesis)
            operatorsBetweenParenthesis++;
    }
    else if(!parenthesis){
        if(!s21_lexem_to_num(&temp, lexem)){
            s21_push(nums, temp);
        }
    }
    if(parenthesis == -1){
        stack_item *last_oper = (stack_item*)malloc(sizeof(stack_item));
        *last_oper =  s21_pop(operators).value;
        while(strcmp(last_oper->oper, "(")){
            s21_intermediate_calculation(nums, last_oper, in_rad, error);
            operatorsBetweenParenthesis--;
            *last_oper =  s21_pop(operators).value;
        }
        s21_top(*operators, last_oper);
        if(last_oper->prio != -1 && s21_is_func(last_oper->oper)){
            *last_oper = s21_pop(operators).value;
            s21_intermediate_calculation(nums, last_oper, in_rad, error);
        }
        if(last_oper!=NULL)
            free(last_oper);
        betweenParenthesis = 0;
    }
}


void s21_set_priority(stack_item *item, stack **operators){
    if(!strcmp(item->oper, "-")){
        stack_item temp;
        s21_top(*operators, &temp);
        if(temp.prio == -1 && temp.oper[0] == '(')
            item->prio = 7;
        else
            item->prio = 1;
    }
    else if(!strcmp(item->oper, "+"))
        item->prio = 1;
    else if(!strcmp(item->oper, "*") || !strcmp(item->oper, ":") || !strcmp(item->oper, "mod"))
        item->prio = 2;
//    else if(lexem == "^")
    else
        item->prio = 3;
}

long double s21_grad_to_rad(long double grad){
    return grad*PI/180;
}

long double s21_rad_to_grad(long double rad){
    return rad*180/PI;
}

int s21_lexem_to_num(stack_item *item, char *lexem){
    int result = 0, dotcount = 0;
    long double new_num = 0;
    for(int i = (int)strlen(lexem) - 1, power = 0; i > -1; i--, power++){
        if(s21_is_digit(lexem[i]) && (lexem[i] != '.')){
            new_num += (lexem[i]-48) * pow(10, power);
        }
        else if((lexem[i] == '.') && (dotcount < 1)){
            new_num *= powl(10, -(power));
            power = -1;
            dotcount++;
        }
        else{
            result = 1;
        }
    }
    if(!result){
        item->number = new_num;
        item->prio = 0;
    }
    return result;
}

