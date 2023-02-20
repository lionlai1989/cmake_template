#include <iostream>
#include <src/geometry/shapes/circle.hpp>
#include <src/geometry/shapes/line.hpp>
#include <src/metric/i2m.hpp>
#include <src/metric/m2i.hpp>
#include <src/semicircle_ruler/semicircle_ruler.hpp>

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
