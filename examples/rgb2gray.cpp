#include <algorithm>
#include <iostream>
#include <mypackage/rgb2gray.hpp>
#include <vector>

class InputParser {
public:
  InputParser(int &argc, char **argv) {
    for (int i = 1; i < argc; ++i)
      this->tokens.push_back(std::string(argv[i]));
  }
  /// @author iain
  const std::string &getCmdOption(const std::string &option) const {
    std::vector<std::string>::const_iterator itr;
    itr = std::find(this->tokens.begin(), this->tokens.end(), option);
    if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
      return *itr;
    }
    static const std::string empty_string("");
    return empty_string;
  }
  /// @author iain
  bool cmdOptionExists(const std::string &option) const {
    return std::find(this->tokens.begin(), this->tokens.end(), option) !=
           this->tokens.end();
  }

private:
  std::vector<std::string> tokens;
};

int main(int argc, char **argv) {
  // std::string rgb_path{
  //     "/home/lai/cmake_template/files/book.png"};
  // std::string gray_path{
  //     "/home/lai/cmake_template/files/book_gray.jpg"};
  InputParser input(argc, argv);
  const std::string &rgb_path = input.getCmdOption("-i");
  const std::string &gray_path = input.getCmdOption("-o");
  const std::string &method = input.getCmdOption("-m");
  std::cout << "Convert the RGB file " << rgb_path << " to the grayscale file "
            << gray_path << '\n';

  if (method == "eigen") {
    mypackage::rgb2gray_image_eigen(rgb_path, gray_path);
  } else if (method == "xtensor") {
    mypackage::rgb2gray_image_xtensor(rgb_path, gray_path);
    mypackage::rgb2gray_image_xtensor_PassByTensor(rgb_path, gray_path);
  } else {
    std::cerr << "Unsuppported rgb2gray method.";
  }
  return 0;
}
