#include <stdio.h>
#include <check.h>
#include "s21_stack.h"
#include "s21_lexem_parse.h"

START_TEST(STACK_NULL_PUSH) {
    stack *test_stack = NULL;
    ck_assert(s21_push(&test_stack, 10, '\0') == SUCCES);
    s21_destroy_stack(test_stack);
}
END_TEST

START_TEST(STACK_NULL_POP) {
    stack *test_stack = NULL;
    ck_assert(s21_pop(test_stack) == NULL);
    s21_destroy_stack(test_stack);
}
END_TEST

START_TEST(STACK_NULL_TOP) {
    stack *test_stack = NULL;
    double value;
    char oper;
    s21_top(test_stack, &value, &oper);
    ck_assert((value == 0) &&(oper == '\0'));
    s21_destroy_stack(test_stack);
}
END_TEST

START_TEST(STACK_ZERO_LENGTH) {
    stack *test_stack = NULL;
    ck_assert(s21_sizeof_stack(test_stack) == 0);
    s21_destroy_stack(test_stack);
}
END_TEST

START_TEST(STACK_NORMAL_LENGTH_1) {
    stack *test_stack = NULL;
    s21_push(&test_stack, 15, '\0');
    s21_push(&test_stack, 15, '\0');
    ck_assert(s21_sizeof_stack(test_stack) == 2);
    s21_destroy_stack(test_stack);
}
END_TEST

START_TEST(STACK_NORMAL_LENGTH_2) {
    stack *test_stack = NULL;
    s21_push(&test_stack, 15, '\0');
    s21_push(&test_stack, 15, '\0');
    stack *last_item = s21_pop(test_stack);
    ck_assert(s21_sizeof_stack(test_stack) == 1);
    s21_destroy_stack(last_item);
    s21_destroy_stack(test_stack);
}
END_TEST

START_TEST(STACK_NORMAL_LENGTH_3) {
    stack *test_stack = NULL;
    s21_push(&test_stack, 15, '\0');
    s21_push(&test_stack, 15, '\0');
    stack *last_item = s21_pop(test_stack);
    s21_destroy_stack(last_item);
    s21_push(&test_stack, 15, '\0');
    s21_push(&test_stack, 15, '\0');
    s21_push(&test_stack, 15, '\0');
    last_item = s21_pop(test_stack);
    ck_assert(s21_sizeof_stack(test_stack) == 3);
    s21_destroy_stack(last_item);
    s21_destroy_stack(test_stack);
}
END_TEST

Suite *s21_stack_test(void) {
    Suite *suite = suite_create("s21_stack");
    TCase *tCase = tcase_create("s21_stack");
    tcase_add_test(tCase, STACK_NULL_PUSH);
    tcase_add_test(tCase, STACK_NULL_POP);
    tcase_add_test(tCase, STACK_NULL_TOP);
    tcase_add_test(tCase, STACK_ZERO_LENGTH);
    tcase_add_test(tCase, STACK_NORMAL_LENGTH_1);
    tcase_add_test(tCase, STACK_NORMAL_LENGTH_2);
    tcase_add_test(tCase, STACK_NORMAL_LENGTH_3);
    suite_add_tcase(suite, tCase);

    return suite;
}

START_TEST(LEXEMS_NORMAL_TEST) {
    char input_string[] = "2+2";
    char correct_lexems[][10] = {"2","+","2"};
    int lexems_count;
    char **lexems = s21_get_lexems(input_string, &lexems_count);
    for(int i = 0; i < 3; i++){
        ck_assert_str_eq(lexems[i], correct_lexems[i]);
    }
    s21_destroy_lexems(lexems, lexems_count);
}
END_TEST

START_TEST(LEXEMS_EMPTY_TEST) {
    char input_string[] = "";
    int lexems_count;
    char **lexems = s21_get_lexems(input_string, &lexems_count);
    ck_assert_ptr_null(lexems);
}
END_TEST

START_TEST(LEXEMS_COMPLEX_TEST) {
    char input_string[] = "1 + 2 * (3 - 4) / 5";
    char correct_lexems[][10] = {"1","+","2","*","(","3","-","4",")","/","5"};
    int lexems_count;
    char **lexems = s21_get_lexems(input_string, &lexems_count);
    for(int i = 0; i < 12; i++){
        ck_assert_str_eq(lexems[i], correct_lexems[i]);
    }
    s21_destroy_lexems(lexems, lexems_count);
}
END_TEST

START_TEST(LEXEMS_SINGLE_NUMBER_TEST) {
    char input_string[] = "123";
    char correct_lexems[][10] = {"123"};
    int lexems_count;
    char **lexems = s21_get_lexems(input_string, &lexems_count);
    ck_assert_str_eq(lexems[0], correct_lexems[0]);
    s21_destroy_lexems(lexems, lexems_count);
}
END_TEST

START_TEST(LEXEMS_SINGLE_OPERATOR_TEST) {
    char input_string[] = "+";
    char correct_lexems[][10] = {"+"};
    int lexems_count;
    char **lexems = s21_get_lexems(input_string, &lexems_count);
    ck_assert_str_eq(lexems[0], correct_lexems[0]);
    s21_destroy_lexems(lexems, lexems_count);
}
END_TEST

START_TEST(LEXEMS_MIXED_TEST) {
    char input_string[] = "12+34*56";
    char correct_lexems[][10] = {"12","+","34","*","56"};
    int lexems_count;
    char **lexems = s21_get_lexems(input_string, &lexems_count);
    for(int i = 0; i < 5; i++){
        ck_assert_str_eq(lexems[i], correct_lexems[i]);
    }
    s21_destroy_lexems(lexems, lexems_count);
}
END_TEST

START_TEST(LEXEMS_PARENTHESES_TEST) {
    char input_string[] = "(2+3)*(4-5)";
    char correct_lexems[][10] = {"(","2","+","3",")","*","(","4","-","5",")"};
    int lexems_count;
    char **lexems = s21_get_lexems(input_string, &lexems_count);
    for(int i = 0; i < 11; i++){
        ck_assert_str_eq(lexems[i], correct_lexems[i]);
    }
    s21_destroy_lexems(lexems, lexems_count);
}
END_TEST

START_TEST(LEXEMS_DECIMAL_NUMBER_TEST) {
    char input_string[] = "3.14";
    char correct_lexems[][10] = {"3.14"};
    int lexems_count;
    char **lexems = s21_get_lexems(input_string, &lexems_count);
    ck_assert_str_eq(lexems[0], correct_lexems[0]);
    s21_destroy_lexems(lexems, lexems_count);
}
END_TEST

START_TEST(LEXEMS_NEGATIVE_NUMBER_TEST) {
    char input_string[] = "-5";
    char correct_lexems[][10] = {"-","5"};
    int lexems_count;
    char **lexems = s21_get_lexems(input_string, &lexems_count);
    for(int i = 0; i < 2; i++){
        ck_assert_str_eq(lexems[i], correct_lexems[i]);
    }
    s21_destroy_lexems(lexems, lexems_count);
}
END_TEST
Suite *s21_get_lexems_test(void) {
    Suite *suite = suite_create("s21_get_lexems");
    TCase *tCase = tcase_create("s21_get_lexems");
    tcase_add_test(tCase, LEXEMS_NORMAL_TEST);
    tcase_add_test(tCase, LEXEMS_EMPTY_TEST);
    tcase_add_test(tCase, LEXEMS_COMPLEX_TEST);
    tcase_add_test(tCase, LEXEMS_SINGLE_NUMBER_TEST);
    tcase_add_test(tCase, LEXEMS_SINGLE_OPERATOR_TEST);
    tcase_add_test(tCase, LEXEMS_MIXED_TEST);
    tcase_add_test(tCase, LEXEMS_PARENTHESES_TEST);
    tcase_add_test(tCase, LEXEMS_DECIMAL_NUMBER_TEST);
    tcase_add_test(tCase, LEXEMS_NEGATIVE_NUMBER_TEST);
    suite_add_tcase(suite, tCase);

    return suite;
}

int main() {
    Suite *suite = s21_stack_test();
    SRunner *sRunner = srunner_create(suite);
    srunner_set_fork_status(sRunner, CK_NOFORK);
    srunner_run_all(sRunner, CK_VERBOSE);
    int total_tests = srunner_ntests_run(sRunner);
    int failed_tests = srunner_ntests_failed(sRunner);
    srunner_free(sRunner);
    suite = s21_get_lexems_test();
    sRunner = srunner_create(suite);
    srunner_set_fork_status(sRunner, CK_NOFORK);
    srunner_run_all(sRunner, CK_VERBOSE);
    total_tests += srunner_ntests_run(sRunner);
    failed_tests += srunner_ntests_failed(sRunner);
    srunner_free(sRunner);

    printf("\nAll tests: %d\n", total_tests);
    printf("Fail tests: %d\n", failed_tests);

    return (failed_tests == 0) ? 0 : 1;
}
