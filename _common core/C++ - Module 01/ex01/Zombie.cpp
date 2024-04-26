#include "Zombie.hpp"

void Zombie::announce(){
    std::cout<<this->name<<": BraiiiiiiinnnzzzZ..."<<std::endl;
}

Zombie::Zombie(std::string name2){
    this->name=name2;
}

Zombie::Zombie(){
    this->name="";
}

Zombie::~Zombie(){
    std::cout<<this->name<<" died."<<std::endl;
}

void Zombie::setZombieName(std::string name2){
	this->name=name2;
}