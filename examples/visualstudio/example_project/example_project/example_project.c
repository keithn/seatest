#include "seatest.h"

void test_fixture_one( void );
void test_fixture_two( void );

void all_tests( void )
{
	test_fixture_one();
	test_fixture_two();
	// add new test fixtures here.
}


int main( int argc, char** argv )
{
	run_tests(all_tests);	
	return 0;
}

