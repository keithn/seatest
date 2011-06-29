#include "../src/seatest.h"

/* Notes:
 *
 *  - if these tests don't run, ensure SEATEST_INTERNAL_TESTS is defined when
 *    compiling
 *
 *  - these tests will report an unreliable test count when run, as they 
 *    reset the pass / fail count 
 */  

void test_foo();
void test_fixture_seatest();
void all_tests();

void test_assert_true()
{
  seatest_reset_count();
  assert_true(1);
  assert_int_equal(1, seatest_get_tests_passed());
  assert_int_equal(0, seatest_get_tests_failed());
}

void test_assert_false()
{
  seatest_reset_count();
  assert_false(0);
  assert_int_equal(1, seatest_get_tests_passed());
  assert_int_equal(0, seatest_get_tests_failed());
}

void test_fixture_seatest(void)
{
  test_fixture_start();      
  run_test(test_assert_true);   
  run_test(test_assert_false);   
  test_fixture_end();       
}

void all_tests(void)
{
  test_fixture_seatest();   
}

int main(int argc, char** argv)
{
  run_tests(all_tests);   
  return 0;
}
