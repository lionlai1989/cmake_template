#include "geometry/shapes/circle.hpp"
#include "geometry/shapes/square.hpp"

namespace src {

double calc_circle_area(double r) {
  src::geometry::shapes::Circle c{1};
  return c.get_area();
}

double calc_square_area(double len) {
  src::geometry::shapes::Square s{2};
  return s.get_area();
}

} // namespace src
