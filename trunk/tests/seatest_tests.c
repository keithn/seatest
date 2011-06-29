#include "seatest_tests.h"

void test_assert_true()
{
  assert_test_passes(assert_true(1)); 
  assert_test_fails(assert_true(0));
}

void test_assert_false()
{
  assert_test_passes(assert_false(0));
  assert_test_fails(assert_false(1));
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
