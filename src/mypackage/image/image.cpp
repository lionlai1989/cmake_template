#include <cassert>
#include <cmath>
#include <eigen-3.4.0/Eigen/Dense>
#include <eigen-3.4.0/unsupported/Eigen/CXX11/Tensor>
#include <filesystem>
#include <iostream>
#include <mypackage/image/image.hpp>
#include <utility>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

namespace mypackage::image {

Image::Image() : channels{0}, height{0}, width{0}, size{0}, pixels{nullptr} {
  std::cout << "The default constructor takes no paramters.\n";
}

Image::Image(std::string file_path) {
  std::cout << "The constructor takes a file's path.\n";
  unsigned char *img_data = stbi_load(file_path.c_str(), &this->width,
                                      &this->height, &this->channels, 0);
  if (img_data == nullptr) {
    const char *error_msg = stbi_failure_reason();
    std::cerr << "Failed to load image: " << file_path.c_str() << "\n";
    std::cerr << "Error msg (stb_image): " << error_msg << "\n";
    std::exit(1);
  }

  this->pixels = std::make_unique<Eigen::Tensor<double, 3>>(
      this->channels, this->height, this->width);
  this->size = this->pixels->size();

  std::cout << "The image shape: " << this->channels << " x " << this->height
            << " x " << this->width << '\n';
  assert(this->size == this->channels * this->height * this->width);
  // this->size = this->width * this->height * this->channels;

  for (int x = 0; x < this->width; x++) {
    for (int y = 0; y < this->height; y++) {
      for (int c = 0; c < this->channels; c++) {
        // NOTE: the order
        int src_idx = y * this->width * this->channels + x * this->channels + c;
        (*this->pixels)(c, y, x) = img_data[src_idx] / 255.;
      }
    }
  }
  // if (this->channels == 4)
  //   this->channels = 3; // ignore alpha channel
  stbi_image_free(img_data);
}

Image::Image(int c, int h, int w)
    : channels{c}, height{h}, width{w}, size{c * h * w},
      pixels{std::make_unique<Eigen::Tensor<double, 3>>(c, h, w)} {
  // NOTE: All members have been initialized.
  std::cout << "The constructor takes c, h, and w.\n";
  // Assign 0 to pixels.
  for (int x = 0; x < this->width; x++) {
    for (int y = 0; y < this->height; y++) {
      for (int c = 0; c < this->channels; c++) {
        (*pixels)(c, y, x) = 0;
      }
    }
  }
}

Image::Image(const Image &other)
    : width{other.width}, height{other.height}, channels{other.channels},
      size{other.size}, pixels{std::make_unique<Eigen::Tensor<double, 3>>(
                            other.channels, other.height, other.width)} {
  std::cout << "Copy Constructor\n";
  for (int x = 0; x < this->width; x++) {
    for (int y = 0; y < this->height; y++) {
      for (int c = 0; c < this->channels; c++) {
        (*pixels)(c, y, x) = (*other.pixels)(c, y, x);
      }
    }
  }
}

Image &Image::operator=(const Image &other) {
  std::cout << "Copy Assignment Operator\n";
  if (this != &other) {
    /** NOTE: `this` could be constructed from the default constructor, which
     * means this->pixels points to nullptr. `this` could also have different
     * size as `other`'s. So, `this->pixels` shall be deleted, and it needs to
     * reallocate new memory with the size of `other`. However, we don't need to
     * call unique_ptr::reset() to delete the object. `this->pixels` will be
     * deleted automatically when `this->pixels` is redirected to another
     * another memory location.
     */
    // this->pixels.reset(); // delete the object, leaving this->pixels empty
    this->pixels = std::make_unique<Eigen::Tensor<double, 3>>(
        other.channels, other.height, other.width);

    this->channels = other.channels;
    this->height = other.height;
    this->width = other.width;
    this->size = other.size;

    for (int x = 0; x < this->width; x++) {
      for (int y = 0; y < this->height; y++) {
        for (int c = 0; c < this->channels; c++) {
          (*this->pixels)(c, y, x) = (*other.pixels)(c, y, x);
        }
      }
    }
  }
  return *this;
}

Image::Image(Image &&other)
    : width{other.width}, height{other.height}, channels{other.channels},
      size{other.size}, pixels{std::move(other.pixels)} {
  /**
   * NOTE: When initializing `pixel`, `pixels{other.pixels}` can not be
   * used. std::move() is needed to transfer the ownership from `other.pixels`
   * to `this.pixel`.
   * https://stackoverflow.com/questions/29194304/move-constructor-involving-const-unique-ptr
   * Moreover, move constructor means that `this` is stealing the resource from
   * `other`. Thus, we don't have to check if `this.pixels` points to nullptr or
   * if the size of `this.pixels` is the same as `other.pixels`.
   */
  std::cout << "Move Constructor\n";

  // Reset all `other`'s members because they are not relevant anymore.
  other.channels = 0;
  other.height = 0;
  other.width = 0;
  other.size = 0;
  other.pixels = nullptr;
}

Image &Image::operator=(Image &&other) {
  std::cout << "Move Assignment Operator\n";
  if (this != &other) {
    this->channels = other.channels;
    this->height = other.height;
    this->width = other.width;
    this->size = other.size;
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
    this->pixels = std::move(other.pixels);
    other.channels = 0;
    other.height = 0;
    other.width = 0;
    other.size = 0;
    other.pixels = nullptr;
  }
  return *this;
}

Image::~Image() { std::cout << "Destruct Image.\n"; }

bool Image::operator==(const Image &other) const {
  /**
   * NOTE: Overload is-equal-to operator. There is only one explicit argument
   * instead of two. The first implicit argument is "this". It does not change
   * the actual object that it is called on, so "const" is put at the end.
   */
  // If at least one element is not the same, set is_equal to false.
  bool is_equal = true;
  for (int x = 0; x < other.width; x++) {
    for (int y = 0; y < other.height; y++) {
      for (int c = 0; c < other.channels; c++) {
        if (((*this->pixels)(c, y, x)) == (*other.pixels)(c, y, x)) {
        } else {
          is_equal = false;
        }
      }
    }
  }
  return this->width == other.width && this->height == other.height &&
         this->channels == other.channels && size == other.size && is_equal;
}

// save image as jpg file
bool Image::save(std::string file_path) {
  auto file_extension = std::filesystem::path(file_path).extension();
  // out_data will be sent to stb API which only takes raw pointer, so
  // unique_ptr is not used here.
  unsigned char *out_data =
      new unsigned char[this->width * this->height * this->channels];
  for (int x = 0; x < this->width; x++) {
    for (int y = 0; y < this->height; y++) {
      for (int c = 0; c < this->channels; c++) {
        int dst_idx = y * this->width * this->channels + x * this->channels + c;
        // Fill out_data with values range 0-255.
        out_data[dst_idx] = std::roundf((*this->pixels)(c, y, x) * 255.);
      }
    }
  }
  bool success;
  if (file_extension == std::string(".jpg") ||
      file_extension == std::string(".JPG")) {
    auto quality = 100;
    success = stbi_write_jpg(file_path.c_str(), this->width, this->height,
                             this->channels, out_data, quality);
  } else if (file_extension == std::string(".png") ||
             file_extension == std::string(".png")) {
    auto stride_in_bytes = this->width * this->channels;
    success = stbi_write_png(file_path.c_str(), this->width, this->height,
                             this->channels, out_data, stride_in_bytes);
  } else {
    std::cerr << "Unsupported file format: " << file_extension << "\n";
  }
  if (!success)
    std::cerr << "Failed to save image: " << file_path << "\n";

  delete[] out_data;
  return true;
}

Image rgb_to_grayscale(const Image &img) {
  assert(img.channels == 3);
  Image gray(1, img.height, img.width);
  for (int x = 0; x < img.width; x++) {
    for (int y = 0; y < img.height; y++) {
      double red, green, blue;
      red = (*img.pixels)(0, y, x);
      green = (*img.pixels)(1, y, x);
      blue = (*img.pixels)(2, y, x);
      (*gray.pixels)(0, y, x) = 0.299 * red + 0.587 * green + 0.114 * blue;
    }
  }
  // gray must be returned by copy but not by reference because it's out of
  // scope.
  return gray;
}

Image get_image_with_ones(int channel, int height, int width) {
  Image img{channel, height, width};
  for (int x = 0; x < img.width; x++) {
    for (int y = 0; y < img.height; y++) {
      for (int c = 0; c < img.channels; c++) {
        (*img.pixels)(c, y, x) = 1.0;
      }
    }
  }
  // std::cout << (*img.pixels) << '\n';
  return img;
}

} // namespace mypackage::image
