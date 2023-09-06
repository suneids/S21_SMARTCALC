#ifndef S21_LEXEM_PARSE_H
#define S21_LEXEM_PARSE_H
char **s21_get_lexems(char *input_string, int *lexems_count);
char *s21_get_next_lexem(char *input_string, int *start_index);
void s21_destroy_lexems(char **lexems, int size);
void s21_remove_spaces(char *input);
#endif
