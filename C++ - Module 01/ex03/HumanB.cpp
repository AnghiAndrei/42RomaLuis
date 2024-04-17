#include "HumanB.hpp"

HumanB::HumanB(std::strign name2){
    this.name=name2;
    this.w=NULL;
}

void HumanB::attack(){
    std::cout<<this.name<<" attacks with their "<<this.w.getType()<<endl;
}

void HumanB::setWeapon(Weapon w2){
    this.w2;
}

HumanB::~Weapon(){
    std::cout<<"HumanB destroyed"<<std::endl;
}