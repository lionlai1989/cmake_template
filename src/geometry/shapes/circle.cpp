#include <iostream>
#include <src/geometry/shapes/circle.h>

Circle::Circle(double radius) : radius(radius) {}

void Circle::display() {
  std::cout << "A circle with radius: " << this->radius << "\n";
}
