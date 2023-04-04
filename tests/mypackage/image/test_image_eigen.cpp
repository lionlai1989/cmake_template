#include <gtest/gtest.h>
#include <iostream>
#include <mypackage/image/image_eigen.hpp>
#include <vector>

TEST(ImageTest, ClassAssertion) {
  mypackage::image::ImageEigen test_img1(2, 3, 4);
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
  mypackage::image::ImageEigen test_img2{test_img1};
  std::clog << "test_img2:\n" << (*test_img2.pixels) << '\n';
  EXPECT_EQ(test_img2, test_img1);

  std::clog << "Test Copy Assignment Operator.\n";
  mypackage::image::ImageEigen test_img3;
  test_img3 = test_img1;
  std::clog << "test_img3:\n" << (*test_img3.pixels) << '\n';
  EXPECT_EQ(test_img3, test_img1);

  mypackage::image::ImageEigen tmp_img{2, 3, 4};
  for (int x = 0; x < tmp_img.width; x++) {
    for (int y = 0; y < tmp_img.height; y++) {
      for (int c = 0; c < tmp_img.channels; c++) {
        (*tmp_img.pixels)(c, y, x) += 1;
      }
    }
  }
  std::clog << "tmp_img:\n" << (*tmp_img.pixels) << '\n';

  std::clog << "Test Move Assignment Operator.\n";
  mypackage::image::ImageEigen test_img4;
  test_img4 = std::move(tmp_img);
  // tmp_img becomes unspecified after it's moved from.
  EXPECT_EQ(tmp_img.pixels, nullptr);
  mypackage::image::ImageEigen test_img5{2, 3, 4};
  (*test_img5.pixels).setConstant(1);
  EXPECT_EQ(test_img5, test_img4);
}
