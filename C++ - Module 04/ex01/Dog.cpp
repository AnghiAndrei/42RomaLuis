#include "Dog.hpp"
void Dog::makeSound() const{std::cout<<"Bau, Bau, N."<<std::endl;}
Dog::~Dog(){
	std::cout<<"Dog destruction"<<std::endl;
	delete this->microb;
}

Dog::Dog() : Animal(){
	this->type="Dog";
	this->microb=new Brain();
	std::cout<<"Dog costruction"<<std::endl;
}

Dog &Dog::operator=(Dog &ncopy){
    this->type=ncopy.type;
    this->microb=ncopy.microb;
    return *this;
}

Dog::Dog(const Dog &ncopy) : Animal(ncopy){
	this->microb=ncopy.microb;
	this->type=ncopy.type;
}