#include <gtest/gtest.h>
#include <iostream>
#include <mypackage/calc.hpp>

TEST(CalcTest, ClassAssertion) {
  double tmp = mypackage::calc_square_area(2);
  EXPECT_EQ(tmp, 2 * 2 * 25.3 * 25.3);
}
