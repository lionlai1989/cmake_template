#ifndef IMAGE_XTENSOR_HPP
#define IMAGE_XTENSOR_HPP

#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xview.hpp>
#include <memory>
#include <string>

namespace mypackage::image {

struct ImageTensor {
  ImageTensor();

  // explicit is always better than implicit.
  explicit ImageTensor(std::string file_path);
  explicit ImageTensor(int c, int h, int w);
  explicit ImageTensor(const ImageTensor &other);

  ImageTensor &operator=(const ImageTensor &other);
  ImageTensor(ImageTensor &&other);
  ImageTensor &operator=(ImageTensor &&other);
  ~ImageTensor();
  bool operator==(const ImageTensor &other) const;

  int channels; // aka comp in std_image
  int height;
  int width;
  int size;
  std::unique_ptr<xt::xtensor<double, 3>> pixels;
  bool save(std::string file_path);
};

ImageTensor rgb_to_grayscale(const ImageTensor &img);
// ImageTensor get_image_with_ones(int channel, int height, int width);
} // namespace mypackage::image

#endif
