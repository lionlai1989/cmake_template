#include <iostream>
#include <src/geometry/shapes/line.h>

Line::Line(double length) : length(length) {}

void Line::display() {
  std::cout << "A line with length: " << this->length << "\n";
}

double Line::get_length() { return this->length; }
