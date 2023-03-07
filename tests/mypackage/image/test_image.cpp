#include <gtest/gtest.h>
#include <iostream>
#include <mypackage/image/image.hpp>

TEST(ImageTest, ClassAssertion) {
    mypackage::image::Image test_img1(3, 4, 5);
std::cout<<(*test_img1.pixels)<< '\n';
  double inch = 2;
  double mm =2 * 25.3;
  EXPECT_EQ(mm, 2 * 25.3);
}
