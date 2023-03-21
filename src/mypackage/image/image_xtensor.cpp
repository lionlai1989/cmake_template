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

// #define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
//#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

namespace mypackage::image {

ImageXTensor::ImageXTensor()
    : channels{0}, height{0}, width{0}, size{0}, pixels{nullptr} {
  std::clog << "The default constructor takes no paramters.\n";
}

ImageXTensor::ImageXTensor(std::string file_path) {
  std::clog << "The constructor takes a file path.\n";

  int tmp_w{0};
  int tmp_h{0};
  int tmp_c{0};

  unsigned char *img_data =
      stbi_load(file_path.c_str(), &tmp_w, &tmp_h, &tmp_c, 0);
  if (img_data == nullptr) {
    const char *error_msg = stbi_failure_reason();
    std::cerr << "Failed to load image: " << file_path.c_str() << "\n";
    std::cerr << "Error msg (stb_image): " << error_msg << "\n";
    std::exit(1);
  }
  channels = tmp_c;
  height = tmp_h;
  width = tmp_w;

  pixels = std::make_unique<xt::xtensor<double, 3>>(
      xt::zeros<double>({channels, height, width}));
  size = pixels->size();

  std::clog << "The image shape: " << channels << " x " << height << " x "
            << width << '\n';
  assert(size == channels * height * width);

  // xt::dynamic_shape<std::size_t> shape;
  // shape.push_back(channels);
  // shape.push_back(height);
  // shape.push_back(width);

  pixels = std::make_unique<xt::xtensor<double, 3>>(
      xt::zeros<double>({height, channels,width}));

  // xt::adapt(img_data, size, *pixels);
  std::copy(img_data, img_data + size, (*pixels).begin());
  
  // auto img = xt::adapt<xt::layout_type::row_major>(img_data,
  //                                                  {height, width,
  //                                                  channels});
  // auto img = xt::adapt_smart_ptr(img_data, {height, width, channels});
  // pixels =
  //     std::make_unique<xt::xtensor<double, 3>>(xt::cast<double>(img) /
  //     255.0);
  (*pixels) = (*pixels) / 255.0;

  // for (int x = 0; x < width; x++) {
  //   for (int y = 0; y < height; y++) {
  //     for (int c = 0; c < channels; c++) {
  //       // PNG's pixels format is mysterious for me.
  //       std::size_t src_idx = y * width * channels + x * channels + c;
  //       // Rescale uint8 to float 0-1.
  //       (*pixels)(c, y, x) = img_data[src_idx] / 255.;
  //     }
  //   }
  // }
  // if (channels == 4)
  //   channels = 3; // ignore alpha channel

  // stbi_image_free(img_data.get());
  stbi_image_free(img_data);
}

ImageXTensor::ImageXTensor(std::size_t c, std::size_t h, std::size_t w)
    : channels{c}, height{h}, width{w}, size{c * h * w},
      pixels{std::make_unique<xt::xtensor<double, 3>>(
          xt::zeros<double>({c, h, w}))} {}

ImageXTensor::ImageXTensor(const ImageXTensor &other)
    : channels{other.channels}, height{other.height}, width{other.width},
      size{other.size}, pixels{std::make_unique<xt::xtensor<double, 3>>(
                            xt::zeros<double>(
                                {other.channels, other.height, other.width}))} {
  std::clog << "Copy Constructor\n";
  /**
   * Take advantage of copy assignment operator of Eigen::Tensor().
   * How funny it is that we are not able to take advantage of copy constructor
   * of Eigen::Tensor() here.
   */
  *pixels = *other.pixels;
  // for (int x = 0; x < width; x++) {
  //   for (int y = 0; y < height; y++) {
  //     for (int c = 0; c < channels; c++) {
  //       (*pixels)(c, y, x) = (*other.pixels)(c, y, x);
  //     }
  //   }
  // }
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
    // Take advantage of copy assignment operator of Eigen::Tensor().
    *pixels = *other.pixels;
  }
  return *this;
}

ImageXTensor::ImageXTensor(ImageXTensor &&other)
    : channels{other.channels}, height{other.height}, width{other.width},
      size{other.size}, pixels{std::move(other.pixels)} {
  /**
   * NOTE: When initializing `pixel`, `pixels{other.pixels}` can not be
   * used. std::move() is needed to transfer the ownership from
   `other.pixels`
   * to `this.pixel`.
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
  // /**
  //  * NOTE: Overload is-equal-to operator. There is only one explicit
  //  argument
  //  * instead of two. The first implicit argument is "this". It does not
  //  change
  //  * the actual object that it is called on, so "const" is put at the end.
  //  */
  // // TODO: Use a BETTER way to compare two eigen tensors are the same or
  // not.
  // // If at least one element is not the same, set is_equal to false.
  // bool is_equal = true;
  // for (int x = 0; x < other.width; x++) {
  //   for (int y = 0; y < other.height; y++) {
  //     for (int c = 0; c < other.channels; c++) {
  //       if (((*pixels)(c, y, x)) == (*other.pixels)(c, y, x)) {
  //       } else {
  //         is_equal = false;
  //       }
  //     }
  //   }
  // }
  // return width == other.width && height == other.height &&
  //        channels == other.channels && size == other.size && is_equal;
}

bool ImageXTensor::save(std::string file_path) {
  /**
   * Save image as jpg or png file
   */
  auto file_extension = std::filesystem::path(file_path).extension();
  // out_data will be sent to stb API which only takes raw pointer, so
  // unique_ptr cannot be used here.
  unsigned char *out_data = new unsigned char[width * height * channels];
  // for (int x = 0; x < width; x++) {
  //   for (int y = 0; y < height; y++) {
  //     for (int c = 0; c < channels; c++) {
  //       int dst_idx = y * width * channels + x * channels + c;
  //       // Fill out_data with values range uint8 0-255.
  //       out_data[dst_idx] = std::roundf((*pixels)(c, y, x) * 255.);
  //     }
  //   }
  // }
  
  //auto tmp = xt::round((*pixels) * 255.);
  xt::xtensor<double, 3> scaled_arr = (*pixels) * 255.;
  xt::xtensor<unsigned char, 3> rounded_arr = xt::round(scaled_arr);
  unsigned char* c_arr = reinterpret_cast<unsigned char*>(rounded_arr.data());

  
  // auto img_view = xt::adapt((*pixels).data(), (*pixels).size());
  // xt::xtensor<unsigned char, 1> out_data =
  //     xt::cast<unsigned char>(xt::round(img_view * 255.0));
  // auto tmp = xt::round((*pixels) * 255.);
  // auto img_view = xt::adapt(xt::eval(tmp).data(), xt::eval(tmp).size());

  bool success;
  if (file_extension == std::string(".jpg") ||
      file_extension == std::string(".JPG")) {
    auto quality = 100;
    success = stbi_write_jpg(file_path.c_str(), width, height, channels,
                             c_arr, quality);
  } else if (file_extension == std::string(".png") ||
             file_extension == std::string(".png")) {
    auto stride_in_bytes = width * channels;
    success = stbi_write_png(file_path.c_str(), width, height, channels,
                             c_arr, stride_in_bytes);
  } else {
    std::cerr << "Unsupported file format: " << file_extension << "\n";
  }
  if (!success)
    std::cerr << "Failed to save image: " << file_path << "\n";

  delete[] out_data;
  return true;
}

ImageXTensor rgb_to_grayscale_xtensor(const ImageXTensor &img) {
  // assert(img.channels == 3);
  //ImageXTensor gray(1, img.height, img.width);
  ImageXTensor gray(img.height, 1, img.width);
  // NOTE: USE gray.pixels = img(0, :, :)*0.299 + img(1, :, :)*0.587 + img(2, :, :)*0.114
  for (auto x = 0; x < img.width; x++) {
    for (auto y = 0; y < img.height; y++) {
      double red, green, blue;
      red = (*img.pixels)(y, 0, x);
      green = (*img.pixels)(y, 1, x);
      blue = (*img.pixels)(y, 2, x);
      // A standard RGB2GRAY equation.
      (*gray.pixels)(y, 0, x) = 0.299 * red + 0.587 * green + 0.114 * blue;
    }
  }
  /**
   * gray cannot be returned by reference because it's out of scope. However, is
   * it possible that gray can be moved to an object in caller function? Eg,
   * caller_gray = std::move(rgb_to_grayscale(img));
   */
  return gray;
}


} // namespace mypackage::image
