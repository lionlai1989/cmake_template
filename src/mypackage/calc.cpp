#include <mypackage/geometry/shapes/circle.hpp>
#include <mypackage/geometry/shapes/square.hpp>
#include <mypackage/calc.hpp>

namespace mypackage {

double calc_circle_area(double r) {
  mypackage::geometry::shapes::Circle c{r};
  return c.get_area();
}

double calc_square_area(double len) {
  mypackage::geometry::shapes::Square s{len};
  return s.get_area();
}

} // namespace mypackage
