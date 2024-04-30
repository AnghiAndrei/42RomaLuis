#include "Animal.hpp"
void Animal::makeSound(void) const{std::cout << "ANIMAL makeSound() called" << std::endl;}
Animal::~Animal(){std::cout<<"Animal destruction"<<std::endl;}
Animal::Animal(const Animal &ncopy){this->type=ncopy.type;}
std::string Animal::getType() const{return this->type;}
Animal::Animal(){this->type="";}
Animal::Animal(std::string type2){
    std::cout<<"Animal costructor"<<std::endl;
    this->type=type2;
}

Animal &Animal::operator=(Animal &ncopy){
    this->type=ncopy.type;
    return *this;
}
