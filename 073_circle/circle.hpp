// circle.hpp

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "point.hpp"  // Assuming Point class is declared in Point.hpp

class Circle {
private:
    Point center;         // Center of the circle
    const double radius;  // Radius of the circle (constant)

public:
    // Constructor that initializes the center and radius
    Circle(const Point& c, double r);

    // Moves the circle's center by (dx, dy)
    void move(double dx, double dy);

    // Computes the area of intersection with another circle
    double intersectionArea(const Circle& otherCircle);
};

#endif // CIRCLE_HPP