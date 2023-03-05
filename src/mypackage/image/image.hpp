#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>

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
  double *data;
  bool save(std::string file_path);
  void set_pixel(int x, int y, int c, double val);
  double get_pixel(int x, int y, int c) const;
};

Image rgb_to_grayscale(const Image &img);

} // namespace mypackage::image

#endif
