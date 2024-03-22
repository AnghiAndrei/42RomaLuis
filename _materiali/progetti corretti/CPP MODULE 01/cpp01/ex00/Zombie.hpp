#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>
#include <string>

class Zombie{
    private:
        std::string _zombieName;

    public:
        Zombie(std::string zombieName);
        ~Zombie(void);
        void announce(void);
};

#endif
