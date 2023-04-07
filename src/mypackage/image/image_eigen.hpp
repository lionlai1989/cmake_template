#ifndef IMAGE_EIGEN_HPP
#define IMAGE_EIGEN_HPP

#include <eigen-3.4.0/unsupported/Eigen/CXX11/Tensor>
#include <memory>
#include <string>

namespace mypackage::image {

struct ImageEigen {
  ImageEigen();

  // explicit is always better than implicit.
  explicit ImageEigen(std::string file_path);
  explicit ImageEigen(int c, int h, int w);
  explicit ImageEigen(const Eigen::Tensor<double, 3> &input_matrix);
  explicit ImageEigen(const ImageEigen &other);
  /**
   * NOTE: move constructor cannot be explicit but copy constructor can. Explain
   * why.
   */
  ImageEigen(ImageEigen &&other);

  ImageEigen &operator=(const ImageEigen &other);
  ImageEigen &operator=(ImageEigen &&other);
  ~ImageEigen();
  bool operator==(const ImageEigen &other) const;

  int channels; // aka comp in std_image
  int height;
  int width;
  int size;
  std::unique_ptr<Eigen::Tensor<double, 3>> pixels;
  bool save(std::string file_path);
};

ImageEigen rgb_to_grayscale_eigen(const ImageEigen &img);
} // namespace mypackage::image

#endif
