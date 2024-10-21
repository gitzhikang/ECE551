#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */

double Vector2D::getMagnitude() const {
  return std::sqrt(x * x + y * y);
}

void Vector2D::print() const {
  printf("<%.2f, %.2f>", x, y);
}
