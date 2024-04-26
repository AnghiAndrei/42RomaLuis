#include "HumanB.hpp"

HumanB::HumanB(std::string name2){
    this->name=name2;
	this->w=NULL;
}

void HumanB::attack(){
	if (w != NULL)
	    std::cout<<this->name<<" attacks with their "<<this->w->getType()<<std::endl;
}

void HumanB::setWeapon(Weapon &w2){
    this->w=&w2;
}