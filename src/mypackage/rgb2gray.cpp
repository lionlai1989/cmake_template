
#include <mypackage/image/image_eigen.hpp>
#include <mypackage/image/image_xtensor.hpp>
#include <mypackage/rgb2gray.hpp>
#include <string>

namespace mypackage {

bool rgb2gray_image_eigen(std::string input, std::string output) {
  mypackage::image::ImageEigen in_img{input};
  auto out_img = mypackage::image::rgb_to_grayscale_eigen(in_img);
  out_img.save(output);
  return 0;
}

bool rgb2gray_image_xtensor(std::string input, std::string output) {
  mypackage::image::ImageXTensor in_img{input};
  auto out_img = mypackage::image::rgb_to_grayscale_xtensor(in_img);
  out_img.save(output);
  return 0;
}

} // namespace mypackage
