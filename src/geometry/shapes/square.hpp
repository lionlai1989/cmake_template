#ifndef SHAPES_LINE_HPP
#define SHAPES_LINE_HPP

#include <string>

namespace src::geometry::shapes {

class Square {
private:
  double side_length;

public:
  Square(double);
  virtual void display();
  virtual double get_area();
};

} // namespace src::geometry::shapes

#endif
