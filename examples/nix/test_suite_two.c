#include "seatest.h"

void test_asserting()
{
	assert_true( 1 == 1);
	assert_false(1 == 2);
	assert_int_equal(1, 1);
}

void test_assert_fails()
{
	assert_true( 1 == 2);
}

void test_fixture_two( void )
{
	test_fixture_start();
	run_test(test_asserting);
	run_test(test_assert_fails);
	test_fixture_end();	
}