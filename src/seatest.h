#ifndef SEATEST_H
#define SEATEST_H
#include <stdio.h>

void seatest_test_suite_start(char* filepath);
void seatest_test_suite_end( void );
void seatest_simple_test_result(int passed, char* reason, char* function, unsigned int line);
void seatest_assert_true(int test, char* function, unsigned int line);
void seatest_assert_false(int test, char* function, unsigned int line);
void seatest_assert_int_equal(int expected, int actual, char* function, unsigned int line);
void seatest_assert_string_equal(char* expected, char* actual, char* function, unsigned int line);
void seatest_assert_string_ends_with(char* expected, char* actual, char* function, unsigned int line);
void seatest_assert_string_starts_with(char* expected, char* actual, char* function, unsigned int line);
void seatest_assert_string_contains(char* expected, char* actual, char* function, unsigned int line);
void seatest_assert_string_doesnt_contain(char* expected, char* actual, char* function, unsigned int line);
int seatest_should_run( char* suite, char* test);
void seatest_run_test(void);
void seatest_setup();
void seatest_teardown();

/*
Assert Macros
*/

#define assert_true(test) do { seatest_assert_true(test, __FUNCTION__, __LINE__); } while (0)
#define assert_false(test) do {  seatest_assert_false(test, __FUNCTION__, __LINE__); } while (0)
#define assert_int_equal(expected, actual) do {  seatest_assert_int_equal(expected, actual, __FUNCTION__, __LINE__); } while (0)
#define assert_string_equal(expected, actual) do {  seatest_assert_string_equal(expected, actual, __FUNCTION__, __LINE__); } while (0)
#define assert_n_array_equal(expected, actual, n) do { int count; for(count=0; count<n; count++) { char s[100]; sprintf(s,"Expected %d to be %d at position %d", actual[count], expected[count], count); seatest_simple_test_result((expected[count] == actual[count]), s, __FUNCTION__, __LINE__);} } while (0)
#define assert_bit_set(bit_number, value) { seatest_simple_test_result(((1 << bit_number) & value), " Expected bit to be set" ,  __FUNCTION__, __LINE__); } while (0)
#define assert_bit_not_set(bit_number, value) { seatest_simple_test_result(!((1 << bit_number) & value), " Expected bit not to to be set" ,  __FUNCTION__, __LINE__); } while (0)
#define assert_bit_mask_matches(value, mask) { seatest_simple_test_result(((value & mask) == mask), " Expected all bits of mask to be set" ,  __FUNCTION__, __LINE__); } while (0)
#define assert_fail(message) { seatest_simple_test_result(0, message,  __FUNCTION__, __LINE__); } while (0)
// assert_bit_count_equal
// assert_struct_equal
// assert_float_equal
// assert_double_equal
#define assert_string_contains(expected, actual) do {  seatest_assert_string_contains(expected, actual, __FUNCTION__, __LINE__); } while (0)
#define assert_string_doesnt_contain(expected, actual) do {  seatest_assert_string_doesnt_contain(expected, actual, __FUNCTION__, __LINE__); } while (0)
#define assert_string_starts_with(expected, actual) do {  seatest_assert_string_starts_with(expected, actual, __FUNCTION__, __LINE__); } while (0)
#define assert_string_ends_with(expected, actual) do {  seatest_assert_string_ends_with(expected, actual, __FUNCTION__, __LINE__); } while (0)

/*
Suite / Test Management
*/

void suite_setup(void (*setup)( void ));
void suite_teardown(void (*teardown)( void ));
#define run_test(test) do { if(seatest_should_run(__FILE__, #test)) {seatest_setup(); test(); seatest_teardown(); seatest_run_test(); }} while (0)
#define test_suite_start() do { seatest_test_suite_start(__FILE__); } while (0)
#define test_suite_end() do { seatest_test_suite_end();} while (0)

void suite_filter(char* filter);
void test_filter(char* filter);

int run_tests(void (*tests)(void));
#endif 