#include "Weapon.hpp"

Weapon::Weapon(std::strign type2){
    this.type=type2;
}

std::string Weapon::setType(){
    this.type=type2;
}

std::string Weapon::getType(){
    return this.type;
}

Weapon::~Weapon(){
    std::cout<<"Weapon destroyed"<<std::endl;
}