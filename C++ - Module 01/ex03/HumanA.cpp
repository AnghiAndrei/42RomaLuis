#include "HumanA.hpp"

HumanA::HumanA(std::string name2, Weapon w2){
    this->name=name2;
    this->w=w2;
}

void HumanA::attack(){
    std::cout<<this->name<<" attacks with their "<<this->w.getType()<<std::endl;
}