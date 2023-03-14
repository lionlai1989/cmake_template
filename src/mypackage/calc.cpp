#include <mypackage/geometry/shapes/square.hpp>
#include <mypackage/calc.hpp>

namespace mypackage {


double calc_square_area(double len) {
  mypackage::geometry::shapes::Square s{len};
  return s.get_area();
}

} // namespace mypackage
