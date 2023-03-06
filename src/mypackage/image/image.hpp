#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <memory>
#include <string>
#include <unsupported/Eigen/CXX11/Tensor>

namespace mypackage::image {

struct Image {
  explicit Image(std::string file_path);
  Image(int w, int h, int c);
  Image();
  ~Image();
  Image(const Image &other);
  Image &operator=(const Image &other);
  Image(Image &&other);
  Image &operator=(Image &&other);
  int width;
  int height;
  int channels;
  int size;
  std::unique_ptr<Eigen::Tensor<double, 3>> pixels;
  bool save(std::string file_path);
};

Image rgb_to_grayscale(const Image &img);

} // namespace mypackage::image

#endif
