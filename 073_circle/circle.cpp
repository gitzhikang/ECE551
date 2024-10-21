// circle.cpp

#include "circle.hpp"
#include <cmath>       // For mathematical functions like sqrt, acos, sin
#include <algorithm>   // For std::min and std::fabs

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Constructor implementation using initializer list
Circle::Circle(const Point& c, double r)
    : center(c), radius(r) {}

// Moves the circle's center by (dx, dy)
void Circle::move(double dx, double dy) {
    center.move(dx, dy);  // Assuming Point class has a move method
}

// Computes the area of intersection with another circle
double Circle::intersectionArea(const Circle& otherCircle){
    // Distance between the centers
    double d = center.distanceFrom(otherCircle.center);

    double r1 = radius;
    double r2 = otherCircle.radius;

    // No overlap
    if (d >= r1 + r2) {
        return 0.0;
    }

    // One circle is completely inside the other
    if (d <= std::fabs(r1 - r2)) {
        double min_radius = std::min(r1, r2);
        return M_PI * min_radius * min_radius;
    }

    // Partial overlap calculation
    double r1_sq = r1 * r1;
    double r2_sq = r2 * r2;

    double part1 = r1_sq * std::acos((d*d + r1_sq - r2_sq) / (2 * d * r1));
    double part2 = r2_sq * std::acos((d*d + r2_sq - r1_sq) / (2 * d * r2));
    double part3 = 0.5 * std::sqrt((-d + r1 + r2) * (d + r1 - r2) *
                                   (d - r1 + r2) * (d + r1 + r2));

    return part1 + part2 - part3;
}