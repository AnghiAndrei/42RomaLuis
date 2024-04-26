#include "Cat.hpp"
void Cat::makeSound() const{std::cout<<"Miao, Miao, N."<<std::endl;}
Cat::~Cat(){
	std::cout<<"Cat destruction"<<std::endl;
	delete this->microb;
}

Cat::Cat() : Animal(){
	this->type="Cat";
	this->microb=new Brain();
	std::cout<<"Cat costruction"<<std::endl;
}

Cat &Cat::operator=(Cat &ncopy){
    this->type=ncopy.type;
    this->microb=ncopy.microb;
    return *this;
}

Cat::Cat(const Cat &ncopy) : Animal(ncopy){
	this->microb=ncopy.microb;
	this->type=ncopy.type;
}