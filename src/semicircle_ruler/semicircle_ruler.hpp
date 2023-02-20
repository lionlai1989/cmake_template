#ifndef SEMICIRCLE_RULER_SEMICIRCLE_RULER_H
#define SEMICIRCLE_RULER_SEMICIRCLE_RULER_H

#include <src/geometry/shapes/circle.hpp>
#include <src/geometry/shapes/line.hpp>

class SemicircleRuler {
private:
  src::geometry::shapes::Line line;
  src::geometry::shapes::Circle circle;
  //   double length;
  //   double radius;

public:
  SemicircleRuler(double length, double radius);
  virtual void draw_line();
  virtual void draw_semicircle();
};

#endif
