#include <gtest/gtest.h>
#include <iostream>
#include <src/geometry/shapes/line.hpp>

TEST(LineTest, ClassAssertion) {
  src::geometry::shapes::Line l{1.0};
  l.display();
  std::cout << l.get_length() << '\n';

  EXPECT_EQ(l.get_length(), 1.0);
}
