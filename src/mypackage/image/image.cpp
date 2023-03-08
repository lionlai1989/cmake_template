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

Image::Image() : width{0}, height{0}, channels{0}, size{0}, pixels{nullptr} {
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

  std::cout << "the image size: " << this->pixels->size() << '\n';
  this->size = this->pixels->size();

  this->size = this->width * this->height * this->channels;
  for (int x = 0; x < this->width; x++) {
    for (int y = 0; y < this->height; y++) {
      for (int c = 0; c < this->channels; c++) {
        // NOTE: the order
        int src_idx = y * this->width * this->channels + x * this->channels + c;
        (*this->pixels)(c, y, x) = img_data[src_idx] / 255.;
      }
    }
  }
  if (this->channels == 4)
    this->channels = 3; // ignore alpha channel
  stbi_image_free(img_data);
}

Image::Image(int c, int h, int w)
    : width{w}, height{h}, channels{c}, size{w * h * c},
      pixels{std::make_unique<Eigen::Tensor<double, 3>>(c, h, w)} {
  std::cout << "The constructor takes w, h, and c.\n";
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
  if (this != &other) {
    std::cout << "Copy Assignment Operator\n";
    // The Image object could be constructed from the default constructor, which
    // means this->pixels points to nullptr.
    this->pixels = std::make_unique<Eigen::Tensor<double, 3>>(
        other.channels, other.height, other.width);
    this->width = other.width;
    this->height = other.height;
    this->channels = other.channels;
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
      size{other.size}, pixels{nullptr} {
  /**
   * NOTE: When initializing `this.pixel`, `pixels{other.pixels}` can not be
   * used. std::move() is needed to transfer the ownership from `other.pixels`
   * to `this.pixel`.
   * https://stackoverflow.com/questions/29194304/move-constructor-involving-const-unique-ptr
   */
  std::cout << "Move Constructor\n";
  // no need to allocate memory for pixels.
  this->pixels = std::move(other.pixels);

  // Reset all the members because they are not relevant anymore.
  other.width = 0;
  other.height = 0;
  other.channels = 0;
  other.size = 0;
  other.pixels = nullptr;
}

Image &Image::operator=(Image &&other) {
  std::cout << "Move Assignment Operator\n";
  this->width = other.width;
  this->height = other.height;
  this->channels = other.channels;
  this->size = other.size;

  // NOTE: We need to check if we need to allocate memory for `this`. `this`
  // could be constructed with the default constructor (ie, with no memory
  // allocation).
  if (this->pixels == nullptr) {
    this->pixels = std::make_unique<Eigen::Tensor<double, 3>>(
        other.channels, other.height, other.width);
  }
  // NOTE: Assign every elements in `*other.pixels` to `(*this->pixels)`. It
  // means `this` and `other` have separate memory allocation for `pixels` but
  // with the identical values.
  for (int x = 0; x < this->width; x++) {
    for (int y = 0; y < this->height; y++) {
      for (int c = 0; c < this->channels; c++) {
        (*this->pixels)(c, y, x) = (*other.pixels)(c, y, x);
      }
    }
  }
  return *this;
}

Image::~Image() { std::cout << "Destruct Image.\n"; }

bool Image::operator==(const Image &other) const {
  // Overload equal-to operator.
  // There is only one explicit argument instead of two. The first implicit
  // argument is "this". It does not change the actual object that it is called
  // on, so "const" is put at the end.
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
  unsigned char *out_data =
      new unsigned char[this->width * this->height * this->channels];
  for (int x = 0; x < this->width; x++) {
    for (int y = 0; y < this->height; y++) {
      for (int c = 0; c < this->channels; c++) {
        int dst_idx = y * this->width * this->channels + x * this->channels + c;
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
