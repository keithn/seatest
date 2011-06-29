#include "seatest_tests.h"

void test_assert_ulong_equal()
{
  assert_test_passes(assert_ulong_equal(1, 1));
  assert_test_passes(assert_ulong_equal(-2, -2));
  assert_test_fails(assert_ulong_equal(1, 0));
  assert_test_fails(assert_ulong_equal(-2, 2));
}

void test_assert_int_equal()
{
  assert_test_passes(assert_int_equal(1, 1));
  assert_test_passes(assert_int_equal(-2, -2));
  assert_test_fails(assert_int_equal(1, 0));
  assert_test_fails(assert_int_equal(-2, 2));
}

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
  run_test(test_assert_int_equal);
  run_test(test_assert_ulong_equal);
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
