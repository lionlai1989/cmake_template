#ifndef SHAPES_CIRCLE_H
#define SHAPES_CIRCLE_H

#include <string>

namespace src::geometry::shapes {

class Circle {
private:
  double radius;

public:
  Circle(double);
  virtual void display();
};

} // namespace src::geometry::shapes

#endif
