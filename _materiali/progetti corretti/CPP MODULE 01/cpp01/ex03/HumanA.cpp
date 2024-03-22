#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &weapon) : _name(name), _weapon(weapon) 
{
    std::cout << "HumanA " << name << " created with " << weapon.getType() << std::endl;
    //return ;
}

HumanA::~HumanA(void)
{
    std::cout << "HumanA " << _name << " destroyed " << std::endl;
}

void HumanA::attack(){
    std::cout << this->_name << " is attacking with a "<< this->_weapon.getType() << std::endl;
}
