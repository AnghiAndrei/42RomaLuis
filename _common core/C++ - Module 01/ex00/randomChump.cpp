#include "Zombie.hpp"

void randomChump(std::string name){
    Zombie newz = Zombie(name);
    newz.announce();
}