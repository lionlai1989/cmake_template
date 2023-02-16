#include <src/semicircle_ruler/semicircle_ruler.h>
#include <iostream>
#include <src/metric/i2m.h>
#include <src/metric/m2i.h>
#include <src/geometry/circle/circle.h>
#include <src/geometry/line/line.h>

SemicircleRuler::SemicircleRuler(double length, double radius):length(length),radius(radius) {}

void SemicircleRuler::measure_length(){
    std::cout << "An object with length: " << "\n";
    double l;
    l = inch2mm(10.0);
}


void SemicircleRuler::measure_angle(){
    std::cout << "A corner with angle: " << "\n";
}
