#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <string>

namespace mypackage::geometry::shapes {

class Square {
private:
  double side_length;

public:
  Square(double);
  virtual void display();
  virtual double get_area();
};

} // namespace mypackage::geometry::shapes

#endif
