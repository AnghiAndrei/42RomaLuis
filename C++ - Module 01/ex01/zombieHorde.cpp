#include "Zombie.hpp"

Zombie  *zombieHorde(int N, std::string name){
    Zombie *orgia=new Zombie[N];
    for(int i=0;i != N; i++)
        orgia[i].setZombieName(name);
    return orgia;
}