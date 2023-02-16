#include <src/geometry/line/line.h>
#include <iostream>

Line::Line(double length):length(length){}

void Line::display(){
	std::cout << "A line with length: " << this->length << "\n";
}

