#include "seatest.h"

void test_strings_equal()
{
	char *s = "hello";
	assert_string_equal("hello", s);
}

void test_arrays_equal()
{
	unsigned char expected_bytes[] = { 1, 2, 3};
	unsigned char buffer[5];
	int i;

	// put 5 bytes in
	for(i=0; i<5; i++) buffer[i]=i+1;

	// only check the first 3
	assert_n_array_equal(expected_bytes, buffer, 3);
}

void test_suite_one( void )
{
	test_suite_start();               // starts a suite
	run_test(test_strings_equal);     // run tests
	run_test(test_arrays_equal);
	test_suite_end();                 // ends a suite
}