#include "s21_calculate.h"
#include "s21_stack.h"
#include "s21_common_funcs.h"
#include "string.h"
#include "math.h"
long double s21_calculate(char *input_string){ 
    long double result = 0, operand1 = 0, operand2 = 0;
    int len = 0, id_operand = 1;
    char **lexems = s21_get_lexems(input_string, &len);
    s21_stack operators, nums;
    for(int i = 0; i < len; i++){
        stack_item new_item;
        if(s21_write_by_value(&new_item, lexems[i])){
            result = 1; //Ошибка
        }
        else{

        }
    }
    s21_destroy_lexems(lexems, len)
    s21_destroy_stack(operators);
    s21_destroy_stack(nums);
    return result;
}


int s21_write_by_value(stack_item *new_item, char *lexem){
    int result = 0;
    stack_item temp =  {0, '\0', -1};
    if(s21_is_oper_or_func(lexem)){// Создание элемента стэка как оператора
        temp.oper = lexem;
    }
    else{
        if(s21_lexem_to_num(&temp, lexem)){
            result = 1;
        }
    }
    *new_item = temp;
    return result;
}


void s21_set_priority(stack_item *item){
    if(lexem == "+" || lexem == "-")
        result = 1;
    else if(lexem == "*" || lexem == "/" || lexem == "mod")
        result = 2;
    else if(lexem == "^")
        result = 3;
    

}


int s21_lexem_to_num(stack_item *item, char *lexem){
    int result = 0, dotcount = 0;
    long double new_num = 0;
    for(int i = (int)strlen(lexem) - 1, power = 0; i > 0; i++, power++){
        if(s21_is_digit(lexem[i]) && (lexem[i] != '.')){
            new_num += (lexem[i]-48) * pow(10, power);
        }
        else if((lexem[i] == '.') && (dotcount < 1)){
            new_num *= 0.1;
            dotcount++;
        }
        else{
            result = 1;
        }
    }
    if(!result){
        item->number = new_num;
    }
    return result;
}

int s21_is_digit(char symbol){
    return (symbol <= '9') && (symbol >= '0');
}