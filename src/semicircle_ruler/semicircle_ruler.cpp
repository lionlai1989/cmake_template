#include <iostream>
#include <src/geometry/shapes/circle.h>
#include <src/geometry/shapes/line.h>
#include <src/metric/i2m.h>
#include <src/metric/m2i.h>
#include <src/semicircle_ruler/semicircle_ruler.h>

SemicircleRuler::SemicircleRuler(double length, double radius)
    : line(length), circle(radius) {}

void SemicircleRuler::draw_line() {

  double l;
  l = src::metric::inch2mm(this->line.get_length());
  std::cout << "An object with length: " << l << "mm.\n";
}

void SemicircleRuler::draw_semicircle() {
  std::cout << "A corner with angle: "
            << "\n";
  this->circle.display();
}
