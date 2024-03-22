#include "Zombie.hpp"

Zombie* newZombie(std::string name);
void randomChump(std::string name);

int main()
{
    Zombie* myZombie = newZombie("HeapZombie");
    myZombie->announce();
    randomChump("stackZombie");
    delete myZombie;
    return 0;
}
