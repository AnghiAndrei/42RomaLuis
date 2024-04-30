#include "AAnimal.hpp"
void AAnimal::makeSound(void) const{std::cout << "AANIMAL makeSound() called" << std::endl;}
AAnimal::~AAnimal(){std::cout<<"AAnimal destruction"<<std::endl;}
AAnimal::AAnimal(const AAnimal &ncopy){this->type=ncopy.type;}
std::string AAnimal::getType() const{return this->type;}
AAnimal::AAnimal(){this->type="";}
AAnimal::AAnimal(std::string type2){
    std::cout<<"AAnimal costructor"<<std::endl;
    this->type=type2;
}

AAnimal &AAnimal::operator=(AAnimal &ncopy){
    this->type=ncopy.type;
    return *this;
}
