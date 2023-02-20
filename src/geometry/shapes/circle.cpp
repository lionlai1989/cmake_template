#include <iostream>
#include <src/geometry/shapes/circle.hpp>

namespace src::geometry::shapes {

Circle::Circle(double radius) : radius(radius) {}

void Circle::display() {
  std::cout << "A circle with radius: " << this->radius << "\n";
}

} // namespace src::geometry::shapes
