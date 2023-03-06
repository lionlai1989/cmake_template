#include <cassert>
#include <cmath>
#include <eigen-3.4.0/Eigen/Dense>
#include <eigen-3.4.0/unsupported/Eigen/CXX11/Tensor>
#include <iostream>
#include <mypackage/image/image.hpp>
#include <utility>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

namespace mypackage::image {

Image::Image(std::string file_path) {
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

Image::Image(int w, int h, int c)
    : width{w}, height{h}, channels{c}, size{w * h * c},
      pixels{std::make_unique<Eigen::Tensor<double, 3>>(c, h, w)} {}

Image::Image() : width{0}, height{0}, channels{0}, size{0}, pixels{nullptr} {}

Image::~Image() {}

Image::Image(const Image &other)
    : width{other.width}, height{other.height}, channels{other.channels},
      size{other.size}, pixels{std::make_unique<Eigen::Tensor<double, 3>>(
                            other.channels, other.height, other.width)} {
  // std::cout << "copy constructor\n";
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
    // std::cout << "copy assignment\n";
    width = other.width;
    height = other.height;
    channels = other.channels;
    size = other.size;

    for (int x = 0; x < this->width; x++) {
      for (int y = 0; y < this->height; y++) {
        for (int c = 0; c < this->channels; c++) {
          (*pixels)(c, y, x) = (*other.pixels)(c, y, x);
        }
      }
    }
  }
  return *this;
}

Image::Image(Image &&other)
    : width{other.width}, height{other.height}, channels{other.channels},
      size{other.size}, pixels{std::make_unique<Eigen::Tensor<double, 3>>(
                            other.channels, other.height, other.width)} {
  // std::cout << "move constructor\n";
  other.size = 0;
}

Image &Image::operator=(Image &&other) {
  // std::cout << "move assignment\n";
  width = other.width;
  height = other.height;
  channels = other.channels;
  size = other.size;

  // pixels = other.pixels;

  // other.data = nullptr;
  other.size = 0;
  return *this;
}

// save image as jpg file
bool Image::save(std::string file_path) {
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
  bool success = stbi_write_jpg(file_path.c_str(), this->width, this->height,
                                this->channels, out_data, 100);
  if (!success)
    std::cerr << "Failed to save image: " << file_path << "\n";

  delete[] out_data;
  return true;
}

Image rgb_to_grayscale(const Image &img) {
  assert(img.channels == 3);
  Image gray(img.width, img.height, 1);
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

} // namespace mypackage::image
