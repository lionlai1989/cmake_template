#include <gtest/gtest.h>
#include <iostream>
#include <mypackage/image/image_eigen.hpp>
#include <vector>

mypackage::image::ImageEigen get_ones_image(int channel, int height,
                                            int width) {
  auto img = mypackage::image::ImageEigen(channel, height, width);
  img.pixels->setConstant(1);
  return img;
}

TEST(ImageTest, ClassAssertion) {
  mypackage::image::ImageEigen test_img(2, 3, 4);
  int counter = 0;
  for (int x = 0; x < test_img.width; x++) {
    for (int y = 0; y < test_img.height; y++) {
      for (int c = 0; c < test_img.channels; c++) {
        (*test_img.pixels)(c, y, x) = counter;
        ++counter;
      }
    }
  }
  std::clog << "test_img:\n" << (*test_img.pixels) << '\n';

  std::clog << "Test Copy Constructor.\n";
  mypackage::image::ImageEigen img_cp_ctor{test_img};
  std::clog << "img_cp_ctor:\n" << (*img_cp_ctor.pixels) << '\n';
  EXPECT_EQ(img_cp_ctor, test_img);

  std::clog << "Test Copy Assignment Operator.\n";
  mypackage::image::ImageEigen img_cp_asgn_otor;
  img_cp_asgn_otor = test_img;
  std::clog << "img_cp_asgn_otor\n" << (*img_cp_asgn_otor.pixels) << '\n';
  EXPECT_EQ(img_cp_asgn_otor, test_img);
  EXPECT_EQ(img_cp_ctor, test_img);

  std::clog << "Test Move Assignment Operator.\n";
  mypackage::image::ImageEigen img_mv_asgn_otor;
  img_mv_asgn_otor = std::move(test_img);
  // test_img becomes unspecified after it's moved from.
  EXPECT_EQ(test_img.pixels, nullptr);
  EXPECT_EQ(img_mv_asgn_otor, img_cp_ctor);

  std::clog << "Test Move Constructor.\n";
  /**
   * NOTE: Move Constructor is not called due to Return Value Optimization.
   * https://en.cppreference.com/w/cpp/language/copy_elision
   */
  mypackage::image::ImageEigen img_mv_ctor{get_ones_image(2, 3, 4)};
  std::clog << "img_mv_ctor:\n" << (*img_mv_ctor.pixels) << '\n';

  std::vector<mypackage::image::ImageEigen> vec;
  /**
   * NOTE: Move Constructor is called because there is no instance construction.
   */
  vec.push_back(get_ones_image(2, 3, 4));
  std::clog << "vec[0]:\n" << *(vec[0].pixels) << '\n';
  mypackage::image::ImageEigen tmp_vec = get_ones_image(2, 3, 4);
  EXPECT_EQ(tmp_vec, vec[0]);
}
