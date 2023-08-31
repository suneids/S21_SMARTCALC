#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "s21_lexem_parse.h"

char** s21_get_lexems(char* input_string, int* lexems_count) {
    input_string = s21_remove_spaces(input_string);
    char** lexems = NULL;
    char* lexem = NULL;
    *lexems_count = 0;
    int start_index = 0;
    if (input_string != NULL && strlen(input_string) > 0) {
        do {
            lexem = s21_get_next_lexem(input_string, &start_index);
            if (lexem != NULL) {
                if (lexems != NULL) {
                    lexems = realloc(lexems, (*lexems_count + 1) * sizeof(char*));
                }
                else {
                    lexems = calloc(2, sizeof(char*));
                }
                lexems[*lexems_count] = lexem;
                (*lexems_count)++;
            }
        } while (start_index < (int)strlen(input_string) && lexem != NULL);
    }
    return lexems;
}

char* s21_get_next_lexem(char* input_string, int* start_index) {
    char* lexem = NULL;
    int lexem_ends = 0, lexem_is_number_or_func = 0, symbol_id = 0;
    char symbol = '\0';
    do {
        symbol = input_string[*start_index];
        int is_single_lexem = s21_is_single(symbol);
        if (is_single_lexem) {
            lexem_ends = 1;
        }
        else {
            lexem_is_number_or_func = 1;
        }
        if (!(lexem_is_number_or_func && is_single_lexem)) {
            if (lexem == NULL) {
                lexem = calloc(2, sizeof(char));
            }
            else {
                lexem = realloc(lexem, (symbol_id + 2) * sizeof(char));
            }
            lexem[symbol_id++] = symbol;
            *start_index = *start_index + 1;
        }
    } while (!lexem_ends && *start_index < (int)strlen(input_string));
    if (lexem != NULL) {
        lexem[symbol_id] = '\0';
    }
    return lexem;
}

int s21_is_single(char symbol) {
    int result = 0;
    char singles[] = "+-*/^()";
    for (int i = 0; i < (int)sizeof(singles) - 1 && !result; i++) {
        if (symbol == singles[i]) {
            result = 1;
        }
    }
    return result;
}

void s21_destroy_lexems(char** lexems, int size) {
    if (lexems != NULL) {
        for (int i = 0; i < size; i++) {
            free(lexems[i]);
        }
        free(lexems);
    }
}

char *s21_remove_spaces(char *input){
    char *result = NULL;
    if(input!=NULL){
        result = (char*)calloc(strlen(input), sizeof(char));
        int i = 0, j = 0;
        while(input[i]){
            if(input[i]!=' '){
                result[j++] = input[i];
            }
        i++;
        }
    }
    return result;
}