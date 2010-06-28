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

void test_bits()
{
	assert_bit_set(0, 0x01);
	assert_bit_set(2, 0x04);
	assert_bit_not_set(3, 0x02);	
}

void test_strings()
{
	char *s = "hello";
	assert_string_equal("hello", s);
	assert_string_contains("blah", "why say blah?");
	assert_string_doesnt_contain("blah", "why say hello?");
	assert_string_ends_with("h?", "why say blah?");
	assert_string_starts_with("why", "why say blah?");
}


void test_suite_one( void )
{
	test_suite_start();               // starts a suite
	run_test(test_strings);   // run tests
	run_test(test_arrays_equal);
	run_test(test_bits);
	test_suite_end();                 // ends a suite
}