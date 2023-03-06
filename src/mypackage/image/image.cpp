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
  this->data = new double[this->size];
  for (int x = 0; x < this->width; x++) {
    for (int y = 0; y < this->height; y++) {
      for (int c = 0; c < this->channels; c++) {

        // NOTE: the order
        int src_idx = y * this->width * this->channels + x * this->channels + c;
        (*this->pixels)(c, y, x) = img_data[src_idx] / 255.;
        int dst_idx = c * this->height * this->width + y * this->width + x;
        this->data[dst_idx] = img_data[src_idx] / 255.;
      }
    }
  }
  if (this->channels == 4)
    this->channels = 3; // ignore alpha channel
  stbi_image_free(img_data);
}

Image::Image(int w, int h, int c)
    : width{w}, height{h}, channels{c}, size{w * h * c},
      data{new double[w * h * c]()},
      pixels{std::make_unique<Eigen::Tensor<double, 3>>(c, w, h)} {}

Image::Image() : width{0}, height{0}, channels{0}, size{0}, data{nullptr} {}

Image::~Image() { delete[] this->data; }

Image::Image(const Image &other)
    : width{other.width}, height{other.height}, channels{other.channels},
      size{other.size}, data{new double[other.size]} {
  // std::cout << "copy constructor\n";
  for (int i = 0; i < size; i++)
    data[i] = other.data[i];
}

Image &Image::operator=(const Image &other) {
  if (this != &other) {
    delete[] data;
    // std::cout << "copy assignment\n";
    width = other.width;
    height = other.height;
    channels = other.channels;
    size = other.size;
    data = new double[other.size];
    for (int i = 0; i < other.size; i++)
      data[i] = other.data[i];
  }
  return *this;
}

Image::Image(Image &&other)
    : width{other.width}, height{other.height}, channels{other.channels},
      size{other.size}, data{other.data} {
  // std::cout << "move constructor\n";
  other.data = nullptr;
  other.size = 0;
}

Image &Image::operator=(Image &&other) {
  // std::cout << "move assignment\n";
  delete[] data;
  data = other.data;
  width = other.width;
  height = other.height;
  channels = other.channels;
  size = other.size;

  other.data = nullptr;
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
        int src_idx = c * this->height * this->width + y * this->width + x;
        out_data[dst_idx] = std::roundf(this->data[src_idx] * 255.);
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

void Image::set_pixel(int x, int y, int c, double val) {
  if (x >= this->width || x < 0 || y >= this->height || y < 0 ||
      c >= this->channels || c < 0) {
    std::cerr << "set_pixel() error: Index out of bounds.\n";
    std::exit(1);
  }
  this->data[c * this->width * this->height + y * this->width + x] = val;
}

double Image::get_pixel(int x, int y, int c) const {
  if (x < 0)
    x = 0;
  if (x >= this->width)
    x = this->width - 1;
  if (y < 0)
    y = 0;
  if (y >= this->height)
    y = this->height - 1;
  return this->data[c * this->width * this->height + y * this->width + x];
}

Image rgb_to_grayscale(const Image &img) {
  assert(img.channels == 3);
  Image gray(img.width, img.height, 1);
  for (int x = 0; x < img.width; x++) {
    for (int y = 0; y < img.height; y++) {
      double red, green, blue;
      red = img.get_pixel(x, y, 0);
      green = img.get_pixel(x, y, 1);
      blue = img.get_pixel(x, y, 2);
      gray.set_pixel(x, y, 0, 0.299 * red + 0.587 * green + 0.114 * blue);
    }
  }
  return gray;
}

} // namespace mypackage::image
