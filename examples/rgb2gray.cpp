#include <iostream>
#include <mypackage/rgb2gray.hpp>

int main(int argc, char **argv) {
  std::string rgb_path{
      "/home/lai/cmake_template/files/book.png"};
  std::string gray_path{
      "/home/lai/cmake_template/files/book_gray.jpg"};
  mypackage::rgb2gray_image(rgb_path, gray_path);
  return 0;
}
