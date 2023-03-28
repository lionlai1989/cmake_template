#include <cassert>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <mypackage/image/image_xtensor.hpp>
#include <utility>
#include <xtensor/xadapt.hpp>
#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xtensor.hpp>
#include <xtensor/xview.hpp>

#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

namespace mypackage::image {

ImageXTensor::ImageXTensor()
    : channels{0}, height{0}, width{0}, size{0}, pixels{nullptr} {
  std::clog << "The default constructor takes no paramters.\n";
}

ImageXTensor::ImageXTensor(std::string file_path) {
  std::clog << "The constructor takes a file path.\n";

  unsigned char *img_data =
      stbi_load(file_path.c_str(), &width, &height, &channels, 0);
  if (img_data == nullptr) {
    const char *error_msg = stbi_failure_reason();
    std::cerr << "Failed to load image: " << file_path.c_str() << "\n";
    std::cerr << "Error msg (stb_image): " << error_msg << "\n";
    std::exit(1);
  }
  pixels = std::make_unique<xt::xtensor<double, 3>>(
      xt::zeros<double>({channels, height, width}));
  /** NOTE: It doesn't make the correct order.
   * pixels = std::make_unique<xt::xtensor<double, 3>>(
   *     xt::adapt<xt::layout_type::row_major>((char *)img_data,
   *                                           {channels, width, height}));
   */

  size = pixels->size();
  std::clog << "The image shape: " << channels << " x " << height << " x "
            << width << '\n';
  assert(size == channels * height * width);

  /**
   * NOTE: It seems like there is no simple/automatic way to reshape 1D array
   * `img_data` to the desired 3D array. Let's say we have an RGB image with 3
   * channels/bands. Each band has shape (height x width). E.g., an RGB image
   * had three bands, and each band's shape is (2 x 4).
   * R band:
   * {{ 1,  4,  7, 10},
   *  {13, 16, 19, 22}}
   * G band:
   * {{ 2,  5,  8, 11},
   *  {14, 17, 20, 23}}
   * B band:
   *{{ 3,  6,  9, 12},
   * {15, 18, 21, 24}}
   *
   * stb library reads this RGB image as 1D array:
   * {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
   *  22, 23, 24}
   *
   * And I cannot find a simple way to convert this 1D array to a 3D (3 x 2 x 4)
   * array with the correct order like following:
   * {{{ 1,  4, 7, 10},
   *   { 13, 16, 19, 22}},
   *  {{ 2,  5, 8, 11},
   *   { 14, 17, 20, 23}},
   *  {{ 3,  6, 9, 12},
   *   { 15, 18, 21, 24}}}
   *
   */
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      for (int c = 0; c < channels; c++) {
        // PNG's pixels order is mysterious for me.
        std::size_t src_idx = y * width * channels + x * channels + c;
        // Rescale uint8 to float 0-1.
        (*pixels)(c, y, x) = img_data[src_idx] / 255.;
      }
    }
  }
  if (channels == 4)
    channels = 3; // ignore alpha channel

  stbi_image_free(img_data);
}

ImageXTensor::ImageXTensor(int c, int h, int w)
    : channels{c}, height{h}, width{w}, size{c * h * w},
      pixels{std::make_unique<xt::xtensor<double, 3>>(
          xt::zeros<double>({c, h, w}))} {}

ImageXTensor::ImageXTensor(const ImageXTensor &other)
    : channels{other.channels}, height{other.height}, width{other.width},
      size{other.size}, pixels{std::make_unique<xt::xtensor<double, 3>>(
                            xt::zeros<double>(
                                {other.channels, other.height, other.width}))} {
  std::clog << "Copy Constructor\n";
  *pixels = *other.pixels;
}

ImageXTensor &ImageXTensor::operator=(const ImageXTensor &other) {
  std::clog << "Copy Assignment Operator\n";
  if (this != &other) {
    channels = other.channels;
    height = other.height;
    width = other.width;
    size = other.size;

    /** NOTE: `this` could be constructed from the default constructor, which
     * means this->pixels points to nullptr. `this` could also have different
     * size as `other`'s. So, `this->pixels` shall be deleted, and it needs to
     * reallocate new memory with the size of `other`. However, we don't need to
     * call `unique_ptr::reset()` to delete the object that `this->pixels`
     * points to. `this->pixels` will be deleted automatically when `unique_ptr`
     * is redirected to another memory location.
     */
    pixels = std::make_unique<xt::xtensor<double, 3>>(
        xt::zeros<double>({other.channels, other.height, other.width}));
    *pixels = *other.pixels;
  }
  return *this;
}

ImageXTensor::ImageXTensor(ImageXTensor &&other)
    : channels{other.channels}, height{other.height}, width{other.width},
      size{other.size}, pixels{std::move(other.pixels)} {
  /**
   * NOTE: When initializing `pixel`, `pixels{other.pixels}` can not be
   * used. std::move() is needed to in order to transfer the ownership from
   * `other.pixels` to `this.pixel`.
   * https://stackoverflow.com/questions/29194304/move-constructor-involving-const-unique-ptr
   * Moreover, move constructor means that `this` is stealing the resource from
   * `other`. Thus, we don't have to check if `this.pixels` points to nullptr or
   * if the size of `this.pixels` is the same as `other.pixels`.
   */
  std::clog << "Move Constructor\n";

  // Reset all `other`'s members because they are not relevant anymore.
  other.channels = 0;
  other.height = 0;
  other.width = 0;
  other.size = 0;
  other.pixels = nullptr;
}

ImageXTensor &ImageXTensor::operator=(ImageXTensor &&other) {
  std::clog << "Move Assignment Operator\n";
  if (this != &other) {
    channels = other.channels;
    height = other.height;
    width = other.width;
    size = other.size;
    /**
     * NOTE: We don't need to check if `this->pixels` points to nullptr or the
     * size of `this->pixels` is the same as `other.pixels`, because
     * `this->pixels` is stealing the resource from `other.pixels`. And the
     * resource that `this->pixels` currently owns will be deleted automatically
     * when `this->pixels` points to another memory location.
     * Also, we need to use std::move() to transfer the ownership of an object.
     * https://stackoverflow.com/questions/26318506/transferring-the-ownership-of-object-from-one-unique-ptr-to-another-unique-ptr-i
     * Finally, remember to reset other.
     */
    pixels = std::move(other.pixels);
    other.channels = 0;
    other.height = 0;
    other.width = 0;
    other.size = 0;
    other.pixels = nullptr;
  }
  return *this;
}

ImageXTensor::~ImageXTensor() { std::clog << "Destruct Image.\n"; }

bool ImageXTensor::operator==(const ImageXTensor &other) const {
  /**
   * NOTE: Overload is-equal-to operator. There is only one explicit argument
   * instead of two. The first implicit argument is "this". It does not change
   * the actual object that it is called on, so "const" is put at the end.
   */
  return (width == other.width) && (height == other.height) &&
         (channels == other.channels) && (size == other.size) &&
         (*pixels == *other.pixels);
}

bool ImageXTensor::save(std::string file_path) {
  /**
   * Save image as jpg or png file
   */
  auto file_extension = std::filesystem::path(file_path).extension();
  /** NOTE: `out_data` will be sent to stb API which only takes raw pointer, so
   * unique_ptr probably cannot be used here.
   */
  unsigned char *out_data = new unsigned char[width * height * channels];
  /** NOTE: There seems to be no easy way to unfold a 3D array into a 1D array
   * with the desired order.
   */
  for (auto x = 0; x < width; x++) {
    for (auto y = 0; y < height; y++) {
      for (auto c = 0; c < channels; c++) {
        int dst_idx = y * width * channels + x * channels + c;
        // Fill out_data with uint8 values range 0-255.
        out_data[dst_idx] = std::roundf((*pixels)(c, y, x) * 255.);
      }
    }
  }

  bool success;
  if (file_extension == std::string(".jpg") ||
      file_extension == std::string(".JPG")) {
    auto quality = 100;
    success = stbi_write_jpg(file_path.c_str(), width, height, channels,
                             out_data, quality);
  } else if (file_extension == std::string(".png") ||
             file_extension == std::string(".png")) {
    auto stride_in_bytes = width * channels;
    success = stbi_write_png(file_path.c_str(), width, height, channels,
                             out_data, stride_in_bytes);
  } else {
    std::cerr << "Unsupported file format: " << file_extension << "\n";
  }
  if (!success)
    std::cerr << "Failed to save image: " << file_path << "\n";

  delete[] out_data;
  return true;
}

ImageXTensor rgb_to_grayscale_xtensor(const ImageXTensor &img) {
  assert(img.channels >= 3);
  ImageXTensor gray(1, img.height, img.width);
  /**
   * Slice r, g and b channels out. NOTE: `red`, `green` and `blue` are 2D.
   */
  xt::xarray<double> red = xt::view(*img.pixels, 0, xt::all(), xt::all());
  xt::xarray<double> green = xt::view(*img.pixels, 1, xt::all(), xt::all());
  xt::xarray<double> blue = xt::view(*img.pixels, 2, xt::all(), xt::all());
  /**
   * `*gray.pixels` is a 3D array. We need to make `red`, `green` and `blue` 3D
   * again before summing them up. However, there might be an easier way to just
   * access the first axis of `*gray.pixels` like we do in numpy:
   * pixels[0, :, :] = 0.299 * red + 0.587 * green + 0.114 * blue
   *
   * *gray.pixels = 0.299 * xt::view(red, xt::newaxis(), xt::all()) +
   *                0.587 * xt::view(green, xt::newaxis(), xt::all()) +
   *                0.114 * xt::view(blue, xt::newaxis(), xt::all());
   */
  /**
   * OK, I figure out how to do it.
   */
  xt::view(*gray.pixels, 0, xt::all(), xt::all()) =
      0.299 * red + 0.587 * green + 0.114 * blue;

  /**
   * This block of code is reserved to remember how to do things manually in the
   * dark age.
   *
   * for (auto x = 0; x < img.width; x++) {
   *   for (auto y = 0; y < img.height; y++) {
   *     double red, green, blue;
   *     red = (*img.pixels)(0, y, x);
   *     green = (*img.pixels)(1, y, x);
   *     blue = (*img.pixels)(2, y, x);
   *     // A standard RGB2GRAY equation.
   *     (*gray.pixels)(0, y, x) = 0.299 * red + 0.587 * green + 0.114 * blue;
   *   }
   * }
   */

  /**
   * gray cannot be returned by reference because it's out of scope. However, is
   * it possible that gray can be moved to an object in caller function? Eg,
   * caller_gray = std::move(rgb_to_grayscale(img));
   */
  return gray;
}

ImageXTensor gaussian_blur(const ImageXTensor &img, double sigma) {
  assert(img.channels == 1);

  int size = std::ceil(6 * sigma);
  if (size % 2 == 0)
    size++;
  int center = size / 2;
  ImageXTensor kernel(size, 1, 1);
  double sum = 0;
  for (int k = -size / 2; k <= size / 2; k++) {
    double val = std::exp(-(k * k) / (2 * sigma * sigma));
    // kernel.set_pixel(center + k, 0, 0, val);
    sum += val;
  }
  for (int k = 0; k < size; k++)
    // kernel.data[k] /= sum;

    ImageXTensor tmp(img.width, img.height, 1);
  ImageXTensor filtered(img.width, img.height, 1);

  // convolve vertical
  for (int x = 0; x < img.width; x++) {
    for (int y = 0; y < img.height; y++) {
      double sum = 0;
      for (int k = 0; k < size; k++) {
        int dy = -center + k;
        // sum += img.get_pixel(x, y + dy, 0) * kernel.data[k];
      }
      // tmp.set_pixel(x, y, 0, sum);
    }
  }
  // convolve horizontal
  for (int x = 0; x < img.width; x++) {
    for (int y = 0; y < img.height; y++) {
      double sum = 0;
      for (int k = 0; k < size; k++) {
        int dx = -center + k;
        // sum += tmp.get_pixel(x + dx, y, 0) * kernel.data[k];
      }
      // filtered.set_pixel(x, y, 0, sum);
    }
  }
  return filtered;
}

} // namespace mypackage::image
