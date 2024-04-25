#include "Cat.hpp"
void Cat::makeSound() const{std::cout<<"Miao, Miao, N."<<std::endl;}
Cat::~Cat(){std::cout<<"Cat destruction"<<std::endl;}
Cat::Cat() : Animal(){
	this->type="Cat";
	std::cout<<"Cat costruction"<<std::endl;
}