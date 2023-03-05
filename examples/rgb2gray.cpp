#include <iostream>
#include <mypackage/image/image.hpp>

int main(int argc, char **argv) {
  std::string rgb_path{
      "/home/lai/cmake_tutorial/my_cmake_template/files/book.png"};
  std::string gray_path{
      "/home/lai/cmake_tutorial/my_cmake_template/files/book_gray.jpg"};
  Image img{rgb_path};

  Image gray = rgb_to_grayscale(img);
  auto ret = gray.save(gray_path);
  std::cout << "return val: " << ret << '\n';
  return 0;
}
