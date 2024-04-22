#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
#include <string>
#include <iostream>
class Zombie{
    std::string name;
    public:
        Zombie(std::string name);
        Zombie();
        ~Zombie();
		void setZombieName(std::string name2);
        void announce(void);
};
Zombie  *zombieHorde(int N, std::string name);
#endif