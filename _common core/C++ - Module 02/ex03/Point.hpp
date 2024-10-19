#ifndef POINT_HPP
#define POINT_HPP
#include <string.h>
#include <iostream>
#include "Fixed.hpp"

class Fixed;

class Point{
	Fixed const x;
	Fixed const y;
    public:
        Point(const Fixed x1, const Fixed y1);
        Point &operator=(const Point &ncopy);
        Point(const Point &ncopy);
        ~Point();
        Point();
		Fixed getX()const;
		Fixed getY()const;
};
#endif