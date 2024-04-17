#include "Zombie.hpp"

Zombie  *zombieHorde(int N, std::string name){
    Zombie *orgia[N+1];
    for(int i=0;i != N; i++)
        orgia[i]= new Zombie(name);
    return orgia
}