#ifndef IMAGE_XTENSOR_HPP
#define IMAGE_XTENSOR_HPP

#include <memory>
#include <string>
#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xview.hpp>

namespace mypackage::image {

struct ImageXTensor {
  ImageXTensor();

  // explicit is always better than implicit.
  explicit ImageXTensor(std::string file_path);
  explicit ImageXTensor(std::size_t c, std::size_t h, std::size_t w);
  explicit ImageXTensor(const ImageXTensor &other);

  ImageXTensor &operator=(const ImageXTensor &other);
  ImageXTensor(ImageXTensor &&other);
  ImageXTensor &operator=(ImageXTensor &&other);
  ~ImageXTensor();
  // bool operator==(const ImageXTensor &other) const;

  int channels; // aka comp in std_image
  int height;
  int width;
  int size;
  std::unique_ptr<xt::xtensor<double, 3>> pixels;
  bool save(std::string file_path);
};

ImageXTensor rgb_to_grayscale_xtensor(const ImageXTensor &img);
// ImageTensor get_image_with_ones(int channel, int height, int width);
} // namespace mypackage::image

#endif
