#include "seatest.h"
#include <conio.h>
#ifdef WIN32
#include "windows.h"
#else
unsigned int GetTickCount() { return 0;}
#endif

static int sea_tests_run = 0;
static int sea_tests_passed = 0;
static int sea_tests_failed = 0;
static char* seatest_current_suite;

char* test_file_name(char* path)
{
	char* file = path + strlen(path);
	while(file != path && *file!= '\\' ) file--;
	if(*file == '\\') file++;
	return file;
}

static int seatest_suite_tests_run;
static int seatest_suite_tests_failed;

void seatest_simple_test_result(int passed, char* reason, char* function, unsigned int line)
{
	if (!passed)
	{
		printf("%-20s Line %-5d %s\r\n", function, line, reason );
		sea_tests_failed++; 
	}
	else
	{
		sea_tests_passed++; 
	}	
}

void seatest_assert_true(int test, char* function, unsigned int line)
{
	seatest_simple_test_result(test, "Should of been true", function, line);
		
}

void seatest_assert_false(int test, char* function, unsigned int line)
{
	seatest_simple_test_result(!test, "Should of been false", function, line);	
}


void seatest_assert_int_equal(int expected, int actual, char* function, unsigned int line)
{
	char s[100];
	sprintf(s, "Expected %d but was %d", expected, actual);
	seatest_simple_test_result(expected==actual, s, function, line);	
}

void seatest_assert_string_equal(char* expected, char* actual, char* function, unsigned int line)
{
	char s[100];
	sprintf(s, "Expected %s but was %s", expected, actual);
	seatest_simple_test_result(strcmp(expected, actual)==0, s, function, line);	
}

void seatest_run_test(void)
{
	 sea_tests_run++; 
}

void seatest_header_printer(char* s, int length, char f)
{
	int l = strlen(s);
	int d = (length- (l + 2)) / 2;
	int i;
	for(i = 0; i<d; i++) printf("%c",f);
	printf(" %s ", s);
	for(i = (d+l+2); i<length; i++) printf("%c",f);
	printf("\r\n");
}


void print_test_suite_header(char* filepath)
{
	seatest_current_suite = test_file_name(filepath);
	seatest_header_printer(seatest_current_suite, 50, '-');
	seatest_suite_tests_failed = sea_tests_failed;
	seatest_suite_tests_run = sea_tests_run;
}

void print_test_suite_footer()
{
	char s[100];
	sprintf(s, "%d run  %d failed", sea_tests_run-seatest_suite_tests_run, sea_tests_failed-seatest_suite_tests_failed);
	seatest_header_printer(s, 50, ' ');
	printf("\r\n");
}

int run_tests(void (*tests)(void))
{
	unsigned long end;
	unsigned long start = GetTickCount();
	tests();	 
	end = GetTickCount();
	printf("\r\n\r\n==================================================\r\n");	 
	if (sea_tests_failed > 0) {
		printf("                      Failed\r\n");			
	}
	else {
		printf("               ALL TESTS PASSED\r\n");
	}
	printf("                 %d tests run\r\n", sea_tests_run);
	printf("                    in %d ms\r\n",end - start);
	printf("==================================================\r\n");

	getch();
	return sea_tests_failed == 0;
}