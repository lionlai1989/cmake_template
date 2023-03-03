#include <geometry/shapes/square.hpp>
#include <gtest/gtest.h>
#include <iostream>

TEST(SquareTest, ClassAssertion) {
  src::geometry::shapes::Square s{2.0};
  s.display();

  EXPECT_EQ(s.get_area(), 4.0);
}
