#include "Zombie.hpp"

Zombie::Zombie(std::string zombieName)
{
    this->_zombieName = zombieName;
    std::cout << this->_zombieName << ": I am alive!" << std::endl;
}
Zombie::~Zombie()
{
        std::cout << this->_zombieName << ": I am destroyed!" << std::endl;
}

void Zombie::announce(void)
{
    std::cout << this->_zombieName << "BraiiiiiiinnnzzzZ..." << std::endl;
}
