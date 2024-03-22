#include "HumanB.hpp"

HumanB::HumanB(std::string name) : _name(name)
{
    std::cout << "HumanB " << name << " created without weapon " << std::endl;
   // std::cout << weapon.getType() << std::endl;

}

HumanB::~HumanB(){
    std::cout << "HumanB " << _name << " destroyed " <<std::endl;
}

void HumanB::attack(){
    if(_weapon){
        std::cout << _name <<" attacks with his " << (*this->_weapon).getType() << std::endl;
    }
    else{
        std::cout <<_name << " attacks with bare hands " << std::endl;
    }
}

void HumanB::setWeapon(Weapon& weapon){
    this->_weapon = &weapon;
}
