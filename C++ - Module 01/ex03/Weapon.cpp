#include "Weapon.hpp"

Weapon::Weapon(std::string type2){
    this->type=type2;
}

Weapon::Weapon(){
    this->type="";
}

void Weapon::setType(std::string type2){
    this->type=type2;
}

std::string& Weapon::getType(){
    return this->type;
}