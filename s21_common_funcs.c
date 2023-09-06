#include "s21_common_funcs.h"
#include "string.h"
int s21_is_oper(char symbol) {
    int result = 0;
    char singles[] = "+-*/^()";
    for (int i = 0; i < (int)strlen(singles) && !result; i++) {
        if (symbol == singles[i]) {
            result = 1;
        }
    }
    return result;
}

int s21_is_oper_or_func(char *lexem) {
    int result = s21_is_oper(lexem[0]);
    if(!result){
        const int funcs_count = 9;
        char funcs[][5] = {"cos", "sin", "tan", "acos", "asin", "atan", "sqrt", "ln", "log"};
        for (int i = 0; i < funcs_count && !result; i++) {
            if (!strcmp(lexem, funcs[i])) {
                result = 1;
            }
        }
    }
    return result;
}
