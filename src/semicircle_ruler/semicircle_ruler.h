#ifndef SEMICIRCLE_RULER_SEMICIRCLE_RULER_H
#define SEMICIRCLE_RULER_SEMICIRCLE_RULER_H

#include <src/geometry/shapes/circle.h>
#include <src/geometry/shapes/line.h>

class SemicircleRuler {
private:
  Line line;
  Circle circle;
  //   double length;
  //   double radius;

public:
  SemicircleRuler(double length, double radius);
  virtual void draw_line();
  virtual void draw_semicircle();
};

#endif
