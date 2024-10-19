#include "Point.hpp"

Point::Point() : x(Fixed( 0 )), y(Fixed( 0 )){;}
Point::Point(const Point &ncopy) : x(ncopy.x), y(ncopy.y){;}
Point::Point(const Fixed x1, const Fixed y1) : x(x1), y(y1){;}
Fixed Point::getX()const {return this->x;}
Fixed Point::getY()const {return this->y;}
Point::~Point(){;}

Point &Point::operator=(const Point &ncopy){
	(void)ncopy;
	return *this;
}