#include "Cat.hpp"
void Cat::makeSound() const{std::cout<<"Miao, Miao, N."<<std::endl;}
Cat::Cat(const Cat &ncopy) : Animal(ncopy){this->type=ncopy.type;}
Cat::~Cat(){std::cout<<"Cat destruction"<<std::endl;}
Cat::Cat() : Animal(){
	this->type="Cat";
	std::cout<<"Cat costruction"<<std::endl;
}

Cat &Cat::operator=(Cat &ncopy){
    this->type=ncopy.type;
    return *this;
}