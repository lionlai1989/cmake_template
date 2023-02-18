#ifndef SHAPES_LINE_H
#define SHAPES_LINE_H

#include <string>

class Line {
private:
  double length;

public:
  Line(double);
  virtual void display();
  virtual double get_length();
};

#endif
