#include "seatest.h"

void test_suite_one( void );
void test_suite_two( void );

void all_tests( void )
{
	test_suite_one();
	test_suite_two();
	// add new test suites here.
}


int main( void )
{
	run_tests(all_tests);
	return 0;
}

