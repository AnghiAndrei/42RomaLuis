#include "ADog.hpp"
void ADog::makeSound() const{std::cout<<"Bau, Bau, N."<<std::endl;}
ADog::~ADog(){std::cout<<"ADog destruction"<<std::endl;}
ADog::ADog() : AAnimal("ADog"){
	std::cout<<"ADog costruction"<<std::endl;
}