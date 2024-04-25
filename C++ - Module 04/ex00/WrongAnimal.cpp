#include "WrongAnimal.hpp"
void WrongAnimal::makeSound(void) const{std::cout << "WrongAnimal makeSound() called" << std::endl;}
WrongAnimal::~WrongAnimal(){std::cout<<"WrongAnimal destruction"<<std::endl;}
WrongAnimal::WrongAnimal(const WrongAnimal &ncopy){this->type=ncopy.type;}
std::string WrongAnimal::getType() const{return this->type;}
WrongAnimal::WrongAnimal(){this->type="";}
WrongAnimal::WrongAnimal(std::string type2){
    std::cout<<"WrongAnimal costructor"<<std::endl;
    this->type=type2;
}

WrongAnimal &WrongAnimal::operator=(WrongAnimal &ncopy){
    this->type=ncopy.type;
    return *this;
}
