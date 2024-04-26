#include "Zombie.hpp"

Zombie* newZombie(std::string name);
void randomChump(std::string name);

int main(){
    Zombie* zombie = newZombie("Heap Sakura");
    zombie->announce();
    randomChump("Stack Hishido");
    delete zombie;
    return 0;
}