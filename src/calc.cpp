#include <geometry/shapes/circle.hpp>
#include <geometry/shapes/square.hpp>
#include <src/calc.hpp>

namespace src {

double calc_circle_area(double r) {
  src::geometry::shapes::Circle c{r};
  return c.get_area();
}

double calc_square_area(double len) {
  src::geometry::shapes::Square s{len};
  return s.get_area();
}

} // namespace src
