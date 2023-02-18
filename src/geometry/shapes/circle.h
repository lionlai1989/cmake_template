#ifndef SHAPES_CIRCLE_H
#define SHAPES_CIRCLE_H

#include <string>

class Circle {
private:
  double radius;

public:
  Circle(double);
  virtual void display();
};

#endif
