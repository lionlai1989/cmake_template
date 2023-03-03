#include <gtest/gtest.h>
#include <iostream>
#include <src/calc.hpp>

TEST(I2mTest, ClassAssertion) {
  double tmp = src::calc_circle_area(1.2);

  EXPECT_EQ(tmp, 2 * 25.3);
}
