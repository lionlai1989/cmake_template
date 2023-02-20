#ifndef SHAPES_LINE_H
#define SHAPES_LINE_H

#include <string>

namespace src::geometry::shapes {

class Line {
private:
  double length;

public:
  Line(double);
  virtual void display();
  virtual double get_length();
};

} // namespace src::geometry::shapes

#endif
