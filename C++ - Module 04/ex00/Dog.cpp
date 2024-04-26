#include "Dog.hpp"
Dog::Dog() : Animal("Dog"){std::cout<<"Dog costruction"<<std::endl;}
void Dog::makeSound() const{std::cout<<"Bau, Bau, N."<<std::endl;}
Dog::Dog(const Dog &ncopy) : Animal(ncopy){this->type=ncopy.type;}
Dog::~Dog(){std::cout<<"Dog destruction"<<std::endl;}

Dog &Dog::operator=(Dog &ncopy){
    this->type=ncopy.type;
    return *this;
}