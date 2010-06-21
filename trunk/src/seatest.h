#ifndef SEATEST_H
#define SEATEST_H
#include <stdio.h>

char* print_test_suite_header(char* s);
void seatest_simple_test_result(int passed, char* reason, char* function, unsigned int line);
void seatest_assert_true(int test, char* function, unsigned int line);
void seatest_assert_false(int test, char* function, unsigned int line);
void seatest_assert_int_equal(int expected, int actual, char* function, unsigned int line);
void seatest_assert_string_equal(char* expected, char* actual, char* function, unsigned int line);
void seatest_run_test(void);

#define assert_true(test) do { seatest_assert_true(test, __FUNCTION__, __LINE__); } while (0)
#define assert_false(test) do {  seatest_assert_false(test, __FUNCTION__, __LINE__); } while (0)
#define assert_int_equal(expected, actual) do {  seatest_assert_int_equal(expected, actual, __FUNCTION__, __LINE__); } while (0)
#define assert_string_equal(expected, actual) do {  seatest_assert_string_equal(expected, actual, __FUNCTION__, __LINE__); } while (0)
#define assert_n_array_equal(expected, actual, n) do { int count; for(count=0; count<n; count++) { char s[100]; sprintf(s,"Expected %d to be %d at position %d", actual[count], expected[count], count); seatest_simple_test_result((expected[count] == actual[count]), s, __FUNCTION__, __LINE__);} } while (0)
#define run_test(test) do { test(); seatest_run_test(); } while (0)
#define test_suite_start() do { print_test_suite_header(__FILE__); } while (0)
#define test_suite_end() do { print_test_suite_footer();} while (0)

int run_tests(void (*tests)(void));

#endif 