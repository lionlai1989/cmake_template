#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <eigen-3.4.0/unsupported/Eigen/CXX11/Tensor>
#include <memory>
#include <string>

namespace mypackage::image {

struct Image {
  Image();

  // Only remove explicit if needed.
  explicit Image(std::string file_path);
  explicit Image(int c, int h, int w);
  explicit Image(const Image &other);
  Image &operator=(const Image &other);
  Image(Image &&other); // can not use explicit
  Image &operator=(Image &&other);
  ~Image();
  bool operator==(const Image &other) const;

  int channels; // aka comp in std_image
  int height;
  int width;
  int size;
  std::unique_ptr<Eigen::Tensor<double, 3>> pixels;
  bool save(std::string file_path);
};

Image rgb_to_grayscale(const Image &img);
Image get_image_with_ones(int channel, int height, int width);
} // namespace mypackage::image

#endif
