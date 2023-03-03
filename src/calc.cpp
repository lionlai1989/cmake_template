#include <geometry/shapes/circle.hpp>
#include <geometry/shapes/square.hpp>
#include <metric/i2m.hpp>
#include <src/calc.hpp>

namespace src {

double calc_circle_area(double r) {
  src::geometry::shapes::Circle c{1};
  // return c.get_area();
  auto t = src::metric::inch2mm(1.2);
  return 1.2;
}

double calc_square_area(double len) {
  src::geometry::shapes::Square s{2};
  // return s.get_area();
  auto t = src::metric::inch2mm(1.2);
  return 1.2;
}

} // namespace src
