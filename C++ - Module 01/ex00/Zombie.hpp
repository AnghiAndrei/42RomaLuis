#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
#include <strign>
#include <iostdlib>
class Zombie{
    str::string name;
    public:
        Zombie(std::string name);
        void announce(void);
        ~Zombie();
};
#endif