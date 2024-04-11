#include "Zombie.h"

Zombie* Zombie::newZombie(std::string name){
    return new Zombie(name);
}