#include "Weapon.hpp"
/*_type(type) initialize the private attribute type*/
Weapon::Weapon(std::string initialType)
{
    this->setType(initialType);
    return ;

}

Weapon::~Weapon(void)
{ 

}

const std::string& Weapon::getType(void)
{
    return (this->_type);
}

void Weapon::setType(std::string initialType)
{
    this->_type = initialType;
}
