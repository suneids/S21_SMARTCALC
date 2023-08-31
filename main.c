#include <stdio.h>
#include <stdlib.h>
#include "../s21_stack.h"
#include "../s21_lexem_parse.h"

int main() {
    char input_string[] = "2+2";
    char correct_lexems[][10] = { "2","+","2" };
    int lexems_count;
    char** lexems = s21_get_lexems(input_string, &lexems_count);
    for (int i = 0; i < 3; i++) {
        printf("%s %s\n",lexems[i], correct_lexems[i]);
    }
    s21_destroy_lexems(lexems, lexems_count);
	return 0;
}