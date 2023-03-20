#ifndef RGB2GRAY_HPP
#define RGB2GRAY_HPP

#include <iostream>

namespace mypackage {
bool rgb2gray_image_eigen(std::string input, std::string output);
bool rgb2gray_image_xtensor(std::string input, std::string output);

} // namespace mypackage

#endif
