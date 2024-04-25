#include "Cat.hpp"
void Cat::makeSound() const{std::cout<<"Miao, Miao, N."<<std::endl;}
Cat::~Cat(){
	std::cout<<"Cat destruction"<<std::endl;
	delete this->microb;
}
Cat::Cat() : Animal(){
	std::cout<<"Cat costruction"<<std::endl;
	this->type="Cat";
	this->microb=new Brain();
}