/* write your class interface in this file
   write function definitions only if they are very short
 */
#include <stdio.h>

#include <cmath>
class Vector2D {
 private:
  double x;
  double y;

 public:

  Vector2D(double x_,double y_):x(x_),y(y_){

  }

  Vector2D():x(0),y(0){

  }

  double getMagnitude() const;

  Vector2D operator+(const Vector2D & rhs) const {
    Vector2D ans(this->x + rhs.x, this->y + rhs.y);
    return ans;
  }

  Vector2D & operator+=(const Vector2D & rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
  }

  double dot(const Vector2D & rhs) const { return this->x * rhs.x + this->y * rhs.y; }
  void print() const;
};
