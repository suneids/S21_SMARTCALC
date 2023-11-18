#include <stdio.h>
#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "../s21_stack.h"
#include "../s21_lexem_parse.h"
#include "../s21_calculate.h"

START_TEST(STACK_NULL_PUSH) {
    stack *test_stack = NULL;
    stack_item new_item = { 10, "\0", 0};
    ck_assert(s21_push(&test_stack, new_item) == SUCCESS);
    s21_destroy_stack(test_stack);
}
END_TEST

START_TEST(STACK_NULL_POP) {
    stack *test_stack = NULL;
    ck_assert(s21_pop(&test_stack).value.prio == -2);
    s21_destroy_stack(test_stack);
}
END_TEST

START_TEST(STACK_NULL_TOP) {
    stack *test_stack = NULL;
    stack_item item;
    s21_top(test_stack, &item);
    ck_assert((item.number == 0) &&(!strcmp(item.oper, "\0")));
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
    stack_item new_item = {15, "\0", 0};
    s21_push(&test_stack, new_item);
    s21_push(&test_stack, new_item);
    ck_assert(s21_sizeof_stack(test_stack) == 2);
    s21_destroy_stack(test_stack);
}
END_TEST

START_TEST(STACK_NORMAL_LENGTH_2) {
    stack *test_stack = NULL;
    stack_item new_item = {15, "\0", 0};
    s21_push(&test_stack, new_item);
    s21_push(&test_stack, new_item);
    s21_pop(&test_stack);
    ck_assert(s21_sizeof_stack(test_stack) == 1);
    s21_destroy_stack(test_stack);
}
END_TEST

START_TEST(STACK_NORMAL_LENGTH_3) {
    stack *test_stack = NULL;
    stack_item new_item = {15, "\0", 0};
    s21_push(&test_stack, new_item);
    s21_push(&test_stack, new_item);
    s21_pop(&test_stack);
    s21_push(&test_stack, new_item);
    s21_push(&test_stack, new_item);
    s21_push(&test_stack, new_item);
    s21_pop(&test_stack);
    ck_assert(s21_sizeof_stack(test_stack) == 3);
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
    char input_string[] = " 1 + 2 * ( 3 - 4 ) / 5";
    char correct_lexems[][10] = {"1","+","2","*","(","3","-","4",")","/","5"};
    int lexems_count = 0;
    char **lexems = s21_get_lexems(input_string, &lexems_count);
    for(int i = 0; i < 11; i++){
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

START_TEST(LEXEMS_BIG_BUFFER_TEST) {
    char input_string[] = "123456789";
    char correct_lexems[][10] = {"123456789"};
    int lexems_count;
    char **lexems = s21_get_lexems(input_string, &lexems_count);
    ck_assert_str_eq(lexems[0], correct_lexems[0]);
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
    tcase_add_test(tCase, LEXEMS_BIG_BUFFER_TEST);
    suite_add_tcase(suite, tCase);

    return suite;
}

START_TEST(CALCULATION_PLUS_SIMPLE_TEST1) {
    int error = 0;
    char input_string[] = "4+4";
    ck_assert_int_eq(s21_calculation(input_string, 0, &error), 8);
}
END_TEST

START_TEST(CALCULATION_PLUS_SIMPLE_TEST2) {
    int error = 0;
    char input_string[] = "4.0+4.0";
    ck_assert_int_eq(s21_calculation(input_string, 0, &error), 8);
}
END_TEST

START_TEST(CALCULATION_PLUS_FLOAT_TEST) {
    int error = 0;
    char input_string[] = "3.0000+4.0000";
    ck_assert_int_eq(s21_calculation(input_string, 0, &error), 7);
}
END_TEST

START_TEST(CALCULATION_MINUS_SIMPLE_TEST) {
    int error = 0;
    char input_string[] = "4-2";
    ck_assert_int_eq(s21_calculation(input_string, 0, &error), 2);
}
END_TEST

START_TEST(CALCULATION_MULTIPLY_SIMPLE_TEST) {
    int error = 0;
    char input_string[] = "4*3";
    ck_assert_int_eq(s21_calculation(input_string, 0, &error), 12);
}
END_TEST

START_TEST(CALCULATION_DIVIDE_SIMPLE_TEST) {
    int error = 0;
    char input_string[] = "4/4";
    ck_assert_int_eq(s21_calculation(input_string, 0, &error), 1);
}
END_TEST

START_TEST(CALCULATION_UNARY_MINUS_SIMPLE_TEST) {
    int error = 0;
    char input_string[] = "-4";
    ck_assert_int_eq(s21_calculation(input_string, 0, &error), -4);
}
END_TEST

START_TEST(CALCULATION_PARENTHESISLESS_1) {
    int error = 0;
    char input_string[] = "4*4+4";
    ck_assert_int_eq(s21_calculation(input_string, 0, &error), 20);
}
END_TEST

START_TEST(CALCULATION_PARENTHESISLESS_2) {
    int error = 0;
    char input_string[] = "4*4+4/4";
    ck_assert_int_eq(s21_calculation(input_string, 0, &error), 17);
}
END_TEST

START_TEST(CALCULATION_PARENTHESISLESS_3) {
    int error = 0;
    char input_string[] = "6/12+4";
    ck_assert_double_eq(s21_calculation(input_string, 0, &error), 4.5);
}
END_TEST

START_TEST(CALCULATION_PARENTHESISLESS_4) {
    int error = 0;
    char input_string[] = "6*1.5";
    ck_assert_double_eq(s21_calculation(input_string, 0, &error), 9);
}
END_TEST

START_TEST(CALCULATION_PARENTHESIS_1) {
    int error = 0;
    char input_string[] = "(8+4)*3/2";
    ck_assert_double_eq(s21_calculation(input_string, 0, &error), 18);
}
END_TEST

START_TEST(CALCULATION_PARENTHESIS_2) {
    int error = 0;
    char input_string[] = "6*(2+7)-5";
    ck_assert_double_eq(s21_calculation(input_string, 0, &error), 49);
}
END_TEST

START_TEST(CALCULATION_PARENTHESIS_3) {
    int error = 0;
    char input_string[] = "12/(4-1)*5";
    ck_assert_double_eq(s21_calculation(input_string, 0, &error), 20);
}
END_TEST

START_TEST(CALCULATION_PARENTHESIS_4) {
    int error = 0;
    char input_string[] = "(3+5)*(4-2)/4";
    ck_assert_double_eq(s21_calculation(input_string, 0, &error), 4);
}
END_TEST

START_TEST(CALCULATION_PARENTHESIS_5) {
    int error = 0;
    char input_string[] = "12*5-8/(6-2)";
    ck_assert_double_eq(s21_calculation(input_string, 0, &error), 58);
}
END_TEST

START_TEST(CALCULATION_PARENTHESIS_6) {
    int error = 0;
    char input_string[] = "9*((5+2)-(6/3))+8";
    ck_assert_double_eq(s21_calculation(input_string, 0, &error), 53);
}
END_TEST

START_TEST(CALCULATION_PARENTHESIS_7) {
    int error = 0;
    char input_string[] = "(7-2)*((4+2)/(9-6))-3";
    ck_assert_double_eq(s21_calculation(input_string, 0, &error), 7);
}
END_TEST

START_TEST(CALCULATION_PARENTHESIS_8) {
    int error = 0;
    char input_string[] = "(12/3)*((4+2)-(8/4))";
    ck_assert_double_eq(s21_calculation(input_string, 0, &error), 16);
}
END_TEST

START_TEST(CALCULATION_FUNCS_1) {
    int error = 0;
    char input_string[] = "sqrt(4)";
    ck_assert_double_eq(s21_calculation(input_string, 0, &error), 2);
}
END_TEST

START_TEST(CALCULATION_FUNCS_2) {
    int error = 0;
    char input_string[] = "sqrt((12/3)*((4+2)-(8/4)))";
    ck_assert_double_eq(s21_calculation(input_string, 0, &error), 4);
}
END_TEST

START_TEST(CALCULATION_FUNCS_3) {
    int error = 0;
    char input_string[] = "sin(90)";
    ck_assert_double_eq(s21_calculation(input_string, 0, &error), 1);
}
END_TEST

START_TEST(CALCULATION_FUNCS_4) {
    int error = 0;
    char input_string[] = "sin(0)";
    ck_assert_double_eq(s21_calculation(input_string, 0, &error), 0);
}
END_TEST

START_TEST(CALCULATION_FUNCS_5) {
    int error = 0;
    char input_string[] = "cos(90)";
    ck_assert_double_eq(s21_calculation(input_string, 0, &error), 0);
}
END_TEST

START_TEST(CALCULATION_FUNCS_6) {
    int error = 0;
    char input_string[] = "cos(0)";
    ck_assert_double_eq(s21_calculation(input_string, 0, &error), 1);
}
END_TEST

START_TEST(CALCULATION_FUNCS_7) {
    int error = 0;
    char input_string[] = "tan(90)";
    s21_calculation(input_string, 0, &error);
    ck_assert_double_eq(error, 1);
}
END_TEST

START_TEST(CALCULATION_FUNCS_8) {
    int error = 0;
    char input_string[] = "tan(0)";
    ck_assert_double_eq(s21_calculation(input_string, 0, &error), 0);
}
END_TEST

START_TEST(CALCULATION_FUNCS_9) {
    int error = 0;
    char input_string[] = "asin(0)";
    ck_assert_double_eq(s21_calculation(input_string, 0, &error), 0);
}
END_TEST

START_TEST(CALCULATION_FUNCS_10) {
    int error = 0;
    char input_string[] = "asin(1)";
    ck_assert_double_eq(s21_calculation(input_string, 0, &error), 90);
}
END_TEST

Suite *s21_calculation_test(void) {
    Suite *suite = suite_create("s21_calculation");
    TCase *tCase = tcase_create("s21_calculation");
    tcase_add_test(tCase, CALCULATION_PLUS_SIMPLE_TEST1);
    tcase_add_test(tCase, CALCULATION_PLUS_SIMPLE_TEST2);
    tcase_add_test(tCase, CALCULATION_PLUS_FLOAT_TEST);
    tcase_add_test(tCase, CALCULATION_MINUS_SIMPLE_TEST);
    tcase_add_test(tCase, CALCULATION_MULTIPLY_SIMPLE_TEST);
    tcase_add_test(tCase, CALCULATION_DIVIDE_SIMPLE_TEST);

    tcase_add_test(tCase, CALCULATION_UNARY_MINUS_SIMPLE_TEST);
    tcase_add_test(tCase, CALCULATION_PARENTHESISLESS_1);
    tcase_add_test(tCase, CALCULATION_PARENTHESISLESS_2);
    tcase_add_test(tCase, CALCULATION_PARENTHESISLESS_3);
    tcase_add_test(tCase, CALCULATION_PARENTHESISLESS_4);

    tcase_add_test(tCase, CALCULATION_PARENTHESIS_1);
    tcase_add_test(tCase, CALCULATION_PARENTHESIS_2);
    tcase_add_test(tCase, CALCULATION_PARENTHESIS_3);
    tcase_add_test(tCase, CALCULATION_PARENTHESIS_4);  
    tcase_add_test(tCase, CALCULATION_PARENTHESIS_5);
    tcase_add_test(tCase, CALCULATION_PARENTHESIS_6);
    tcase_add_test(tCase, CALCULATION_PARENTHESIS_7);
    tcase_add_test(tCase, CALCULATION_PARENTHESIS_8); 

    tcase_add_test(tCase, CALCULATION_FUNCS_1);
    tcase_add_test(tCase, CALCULATION_FUNCS_2);
    tcase_add_test(tCase, CALCULATION_FUNCS_3);
    tcase_add_test(tCase, CALCULATION_FUNCS_4);
    tcase_add_test(tCase, CALCULATION_FUNCS_5);
    tcase_add_test(tCase, CALCULATION_FUNCS_6);
    tcase_add_test(tCase, CALCULATION_FUNCS_7);
    tcase_add_test(tCase, CALCULATION_FUNCS_8);
    tcase_add_test(tCase, CALCULATION_FUNCS_9);
    tcase_add_test(tCase, CALCULATION_FUNCS_10);
    suite_add_tcase(suite, tCase);
    return suite;
}

START_TEST(VALIDATOR_TEST_1) {
    int error = 0;
    char input_string[] = "asin(1)";
    ck_assert_double_eq(s21_calculation(input_string, 0, &error), 90);
}
END_TEST

Suite *s21_validator_test(void) {
    Suite *suite = suite_create("s21_validator");
    TCase *tCase = tcase_create("s21_validator");
    tcase_add_test(tCase, VALIDATOR_TEST_1);
    suite_add_tcase(suite, tCase);
    return suite;
}

int main() {
    //stack test
    Suite *suite = s21_stack_test();
    SRunner *sRunner = srunner_create(suite);
    srunner_set_fork_status(sRunner, CK_NOFORK);
    srunner_run_all(sRunner, CK_VERBOSE);
    int total_tests = srunner_ntests_run(sRunner);
    int failed_tests = srunner_ntests_failed(sRunner);
    srunner_free(sRunner);
    
    //lexems test
    suite = s21_get_lexems_test();
    sRunner = srunner_create(suite);
    srunner_set_fork_status(sRunner, CK_NOFORK);
    srunner_run_all(sRunner, CK_VERBOSE);
    total_tests += srunner_ntests_run(sRunner);
    failed_tests += srunner_ntests_failed(sRunner);
    srunner_free(sRunner);

    //calculation test
    suite = s21_calculation_test();
    sRunner = srunner_create(suite);
    srunner_set_fork_status(sRunner, CK_NOFORK);
    srunner_run_all(sRunner, CK_VERBOSE);
    total_tests += srunner_ntests_run(sRunner);
    failed_tests += srunner_ntests_failed(sRunner);
    srunner_free(sRunner);


    //validator test
    suite = s21_validator_test();
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
