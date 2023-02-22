#include <iostream>
#include <src/geometry/shapes/square.hpp>
#include <src/metric/i2m.hpp>

namespace src::geometry::shapes {

Square::Square(double length) { side_length = src::metric::inch2mm(length); }

void Square::display() {
  std::cout << "A square with side length: " << this->side_length << " mm.\n";
}

double Square::get_area() { return this->side_length * this->side_length; }

} // namespace src::geometry::shapes
