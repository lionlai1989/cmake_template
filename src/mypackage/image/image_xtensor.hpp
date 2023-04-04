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
  /**
   * NOTE: move constructor cannot be explicit but copy constructor can. Explain
   * why.
   */
  ImageXTensor(ImageXTensor &&other);

  ImageXTensor &operator=(const ImageXTensor &other);
  ImageXTensor &operator=(ImageXTensor &&other);
  ~ImageXTensor();
  bool operator==(const ImageXTensor &other) const;

  int channels; // aka comp in std_image
  int height;
  int width;
  int size;
  std::unique_ptr<xt::xtensor<double, 3>> pixels;

  bool save(std::string file_path);
  void swap(ImageXTensor &other);
};

/**
 * NOTE: The following two functions have the same name but with different
 * signatures.
 */
ImageXTensor rgb_to_grayscale_xtensor(const ImageXTensor &img);
xt::xarray<double> rgb_to_grayscale_xtensor(const xt::xarray<double> &pixels);

} // namespace mypackage::image

#endif
