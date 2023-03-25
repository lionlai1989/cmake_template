#include <gtest/gtest.h>
#include <iostream>
#include <mypackage/image/image_xtensor.hpp>
#include <vector>
#include <xtensor/xadapt.hpp>

TEST(ImageXTensor, ClassAssertion) {
  mypackage::image::ImageXTensor test_img1(2, 3, 4);
  int counter = 0;
  for (int x = 0; x < test_img1.width; x++) {
    for (int y = 0; y < test_img1.height; y++) {
      for (int c = 0; c < test_img1.channels; c++) {
        (*test_img1.pixels)(c, y, x) = counter;
        ++counter;
      }
    }
  }
  std::clog << "test_img1:\n" << (*test_img1.pixels) << '\n';

  std::clog << "Test Copy Constructor.\n";
  mypackage::image::ImageXTensor test_img2{test_img1};
  std::clog << "test_img2\n" << (*test_img2.pixels) << '\n';
  EXPECT_EQ(test_img2, test_img1);

  std::clog << "Test Copy Assignment Operator.\n";
  mypackage::image::ImageXTensor test_img3;
  test_img3 = test_img1;
  std::clog << "test_img3\n" << (*test_img3.pixels) << '\n';
  EXPECT_EQ(test_img3, test_img1);

  std::clog << "Test Move Assignment Operator.\n";
  mypackage::image::ImageXTensor test_img4;
  test_img4 = std::move(test_img1); // test_img1 is unspecified.
  EXPECT_EQ(test_img1.pixels, nullptr);
  EXPECT_EQ(test_img4, test_img2);
}
