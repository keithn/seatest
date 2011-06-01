#include "seatest.h"

void test_fixture_one( void );
void test_fixture_two( void );

void all_tests( void )
{
	test_fixture_one();
	test_fixture_two();
	// add new test fixtures here.
}

void my_suite_setup( void )
{
	//printf("I'm done before every single test in the suite\r\n");
}

void my_suite_teardown( void )
{
	//printf("I'm done after every single test in the suite\r\n");
}

int main( int argc, char** argv )
{
	return seatest_testrunner(argc, argv, all_tests, my_suite_setup, my_suite_teardown);	
}

/*************************************************************************************************************************************************************/
/*  Everything after this point are just alternative "main" functions which show different ways you can run the tests....they don't get used in this example */
/*************************************************************************************************************************************************************/

/*
Use this if you don't have any global setup/teardown...
*/
int main_no_setup_or_teardown( int argc, char** argv )
{
	return seatest_testrunner(argc, argv, all_tests, NULL, NULL);	
}

/*
Use this if you don't want to use the test runner...
*/
int main_do_it_myself( int argc, char** argv )
{
	suite_setup(my_suite_setup);
	suite_teardown(my_suite_teardown); 
	return run_tests(all_tests);	
}

/*
Use this if you don't want to use the test runner and don't have any global setup/teardown...
*/
int main_do_it_myself_really_simply( int argc, char** argv )
{	
	return run_tests(all_tests);	
}

