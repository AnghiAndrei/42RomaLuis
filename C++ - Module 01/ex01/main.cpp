#include "Zombie.hpp"
int main(){
    int n = 5;
    Zombie *horde = zombieHorde(n, "Duplicate");
    for(int i = 0; i != n; i++)
        horde[i].announce();
    delete [] horde;
    return 0;
}