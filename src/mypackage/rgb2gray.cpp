
#include <mypackage/rgb2gray.hpp>
#include <string>
#include <mypackage/image/image.hpp>

namespace mypackage {

bool rgb2gray_image(std::string input, std::string output) {
  mypackage::image::Image in_img{input};
  auto out_img = mypackage::image::rgb_to_grayscale(in_img);
  out_img.save(output);
  return 0;
}

} // namespace mypackage
