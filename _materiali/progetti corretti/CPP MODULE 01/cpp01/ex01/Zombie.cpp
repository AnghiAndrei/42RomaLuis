#include "Zombie.hpp"

Zombie::Zombie(std::string zombieName)
{
    this->_zombieName = zombieName;
    std::cout << this->_zombieName << ": I am alive!" << std::endl;
}

Zombie::Zombie(void){
    this->_zombieName = "(null)";
    std::cout << this->_zombieName << ": I am alive!" << std::endl;
}

Zombie::~Zombie() {
        std::cout << this->_zombieName << ": I am destroyed!" << std::endl;
}

void Zombie::announce(void){
    std::cout << this->_zombieName << "BraiiiiiiinnnzzzZ..." << std::endl;
}

void	Zombie::setZombieName(std::string _zombieName)
{
	this->_zombieName = _zombieName;
}
