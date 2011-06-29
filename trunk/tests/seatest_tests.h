#include "../src/seatest.h"

#ifndef SEATEST_INTERNAL_TESTS
#error SEATEST_INTERNAL_TESTS must be defined when compiling tests for SeaTest itself.
#endif

#define without_logging(X) seatest_disable_logging(); X; seatest_enable_logging();
#define assert_test_passes(X) without_logging(X); seatest_assert_last_passed();
#define assert_test_fails(X) without_logging(X); seatest_assert_last_failed();

void test_assert_true();
void test_assert_false();
void test_fixture_seatest();
void all_tests();

