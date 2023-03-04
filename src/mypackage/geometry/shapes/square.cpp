#include <iostream>
#include <mypackage/geometry/shapes/square.hpp>
#include <mypackage/metric/i2m.hpp>

namespace mypackage::geometry::shapes {

Square::Square(double length) { side_length = mypackage::metric::inch2mm(length); }

void Square::display() {
  std::cout << "A square with side length: " << this->side_length << " mm.\n";
}

double Square::get_area() { return this->side_length * this->side_length; }

} // namespace mypackage::geometry::shapes
