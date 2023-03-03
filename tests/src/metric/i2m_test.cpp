#include <gtest/gtest.h>
#include <iostream>
#include <metric/i2m.hpp>

TEST(I2mTest, ClassAssertion) {
  double inch = 2;
  double mm = src::metric::inch2mm(inch);

  EXPECT_EQ(mm, 2 * 25.3);
}
