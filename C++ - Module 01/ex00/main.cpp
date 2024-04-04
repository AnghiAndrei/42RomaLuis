#include "Zombie.h"

int main(){
    Zombie z=Zombie("Sakura");
    z.announce();
    Zombie *z2=z.newZombie("Hishido");
    *z2.announce();
    randomChump("Aka");
    delete z;
    delete z2;
    return 0;
}