#include "Zombie.hpp"
int main(){
    int n = -5;
    Zombie *horde = zombieHorde(n, "Duplicate");
	if (horde == NULL)
		return (std::cout<<"Oh capito che semo morti ma manco a fa cosi!!!"<<std::endl, 1);
    for(int i = 0; i != n; i++)
        horde[i].announce();
    delete [] horde;
    return 0;
}