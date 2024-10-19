#include "Fixed.hpp"
#include "Point.hpp"

static Fixed area(Point const a, Point const b, Point const c){
	return (
			(a.getX()*(b.getY()-c.getY()))+
			(b.getX()*(c.getY()-a.getY()))+
			(c.getX()*(a.getY()-b.getY()))
		)/2;
}
static Fixed abs(Fixed n){
	if (n < 0)
		return n * -1;
	return n;
}

static bool isOnLine(const Point& p1, const Point& p2, const Point& p){
	Fixed m = (p2.getY() - p1.getY()) / (p2.getX() - p1.getX());
    Fixed expectedY = m * (p.getX() - p1.getX()) + p1.getY();
    return (p.getY() >= std::min(p1.getY(), p2.getY()) && p.getY() <= std::max(p1.getY(), p2.getY()) && expectedY == p.getY());
}

template<typename T>
T min(T val1, T val2){
    if(val1>val2)		return val2;
    else if(val1<val2)	return val1;
    else if(val1==val2)	return val2;
	return val2;
}

template<typename T>
T max(T val1, T val2){
    if(val1<val2)		return val2;
    else if(val1>val2)	return val1;
    else if(val1==val2)	return val2;
	return val2;
}

bool bsp(Point const a, Point const b, Point const c, Point const point){
	if (a.getX()==point.getX() && a.getY()==point.getY())
		return false;
	if (b.getX()==point.getX() && b.getY()==point.getY())
		return false;
	if (c.getX()==point.getX() && c.getY()==point.getY())
		return false;

	if (isOnLine(a, b, point) || isOnLine(a, c, point) || isOnLine(b, c, point))return false;

	Fixed abc_area=abs(area(a, b, c));
	Fixed pab_area=abs(area(point, a, b));
	Fixed pbc_area=abs(area(point, b, c));
	Fixed pca_area=abs(area(point, c, a));
	return abc_area==pab_area+pbc_area+pca_area;
}