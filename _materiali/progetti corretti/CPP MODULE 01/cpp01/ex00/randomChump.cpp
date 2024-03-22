#include "Zombie.hpp"

void randomChump(std::string name)
{
    Zombie z = Zombie(name);
    z.announce();
}
