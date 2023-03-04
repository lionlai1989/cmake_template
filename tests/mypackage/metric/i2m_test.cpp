#include <gtest/gtest.h>
#include <iostream>
#include <mypackage/metric/i2m.hpp>

TEST(I2mTest, ClassAssertion) {
  double inch = 2;
  double mm = mypackage::metric::inch2mm(inch);
  EXPECT_EQ(mm, 2 * 25.3);
}
