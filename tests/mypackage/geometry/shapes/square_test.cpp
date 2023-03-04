#include <gtest/gtest.h>
#include <mypackage/geometry/shapes/square.hpp>

TEST(SquareTest, ClassAssertion) {
  mypackage::geometry::shapes::Square s{2.0};
  EXPECT_EQ(s.get_area(), 2 * 2 * 25.3 * 25.3);
}
