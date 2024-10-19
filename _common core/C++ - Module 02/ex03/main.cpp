#include "Point.hpp"

bool bsp(Point const a, Point const b, Point const c, Point const point);

int main(){
	std::cout<<"Ora vi insegnio a giudare... ..."<<std::endl;
	/*
		prende il palo:
		 30, 45

		non prende il palo:
		-30, 45 non prende il palo
		 10, 30 non prende il palo
		  60, 0 non prende il palo
	*/
	if(bsp(Point(0, 0), Point(30, 90), Point(60, 0), Point(30, 45)))
		std::cout<<"Ho preso il palo frateli..."<<std::endl;
	else
		std::cout<<"Non ho preso il palo frateli..."<<std::endl;
	return 0;
}