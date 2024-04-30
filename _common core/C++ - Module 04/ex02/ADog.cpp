#include "ADog.hpp"
void ADog::makeSound() const{std::cout<<"Bau, Bau, N."<<std::endl;}
ADog::~ADog(){
	std::cout<<"ADog destruction"<<std::endl;
	delete this->microb;
}

ADog::ADog() : AAnimal(){
	this->type="ADog";
	this->microb=new Brain();
	std::cout<<"ADog costruction"<<std::endl;
}

ADog &ADog::operator=(ADog &ncopy){
    this->type=ncopy.type;
    this->microb=ncopy.microb;
    return *this;
}

ADog::ADog(const ADog &ncopy) : AAnimal(ncopy){
	this->microb=ncopy.microb;
	this->type=ncopy.type;
}