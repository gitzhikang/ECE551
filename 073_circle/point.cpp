#include "point.hpp"
#include <cmath>
using std::sqrt;
void Point::move(double dx,double dy){
    this->x +=dx;
    this->y +=dy;
}

double Point::distanceFrom(const Point & p){
    return sqrt((this->x-p.x)*(this->x-p.x)+(this->y-p.y)*(this->y-p.y));
}