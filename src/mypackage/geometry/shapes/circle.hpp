#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <string>

namespace mypackage::geometry::shapes {

class Circle {
private:
  double radius;

public:
  Circle(double);
  virtual void display();
  virtual double get_area();
};

} // namespace mypackage::geometry::shapes

#endif
