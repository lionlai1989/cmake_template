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
  explicit ImageXTensor(int c, int h, int w);
  explicit ImageXTensor(const ImageXTensor &other);

  ImageXTensor &operator=(const ImageXTensor &other);
  ImageXTensor(ImageXTensor &&other);
  ImageXTensor &operator=(ImageXTensor &&other);
  ~ImageXTensor();
  bool operator==(const ImageXTensor &other) const;

  int channels; // aka comp in std_image
  int height;
  int width;
  int size;
  std::unique_ptr<xt::xtensor<double, 3>> pixels;
  bool save(std::string file_path);
};

ImageXTensor rgb_to_grayscale_xtensor(const ImageXTensor &img);
ImageXTensor gaussian_blur(const ImageXTensor &img, double sigma);
} // namespace mypackage::image

#endif
