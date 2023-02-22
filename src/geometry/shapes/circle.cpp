#include <iostream>
#include <src/geometry/shapes/circle.hpp>
#include <src/metric/i2m.hpp>

namespace src::geometry::shapes {

Circle::Circle(double radius) { radius = src::metric::inch2mm(radius); }

void Circle::display() {
  std::cout << "A circle with radius: " << this->radius << " mm.\n";
}

double Circle::get_area() { return 3.14 * this->radius * this->radius; }

} // namespace src::geometry::shapes
