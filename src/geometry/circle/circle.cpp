#include <src/geometry/circle/circle.h>
#include <iostream>

Circle::Circle(double radius):radius(radius){}

void Circle::display(){
	std::cout << "A circle with radius: " << this->radius << "\n";
}

