#include <iostream>
#include <mypackage/geometry/shapes/circle.hpp>
#include <mypackage/metric/i2m.hpp>

namespace mypackage::geometry::shapes {

Circle::Circle(double radius) { radius = mypackage::metric::inch2mm(radius); }

void Circle::display() {
  std::cout << "A circle with radius: " << this->radius << " mm.\n";
}

double Circle::get_area() { return 3.14 * this->radius * this->radius; }

} // namespace mypackage::geometry::shapes
