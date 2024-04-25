#include "Dog.hpp"
void Dog::makeSound() const{std::cout<<"Bau, Bau, N."<<std::endl;}
Dog::~Dog(){std::cout<<"Dog destruction"<<std::endl;}
Dog::Dog() : Animal("Dog"){std::cout<<"Dog costruction"<<std::endl;}