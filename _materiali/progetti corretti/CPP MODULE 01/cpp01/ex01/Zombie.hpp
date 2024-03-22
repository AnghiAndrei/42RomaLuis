#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>
#include <string>

class Zombie
{
    private:
        std::string _zombieName;

    public:
        Zombie(std::string zombieName);
        Zombie(void);
        ~Zombie(void);
        void announce(void);
        void setZombieName(std::string name);
};

Zombie* newZombie(std::string name);
void randomChump(std::string name);
#endif
