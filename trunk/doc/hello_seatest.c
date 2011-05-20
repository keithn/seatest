#include "seatest.h"
//
// create a test...
//
void test_hello_world()
{
	char *s = "hello world!";
	assert_string_equal("hello world!", s);
	assert_string_contains("hello", s);
	assert_string_doesnt_contain("goodbye", s);
	assert_string_ends_with("!", s);
	assert_string_starts_with("hell", s);
}

//
// put the test into a fixture...
//
void test_fixture_hello( void )
{
	test_fixture_start();      
	run_test(test_hello_world);   
	test_fixture_end();       
}

//
// put the fixture into a suite...
//
void all_tests( void )
{
	test_fixture_hello();	
}

//
// run the suite!
//
int main( int argc, char** argv )
{
	run_tests(all_tests);	
	return 0;
}
