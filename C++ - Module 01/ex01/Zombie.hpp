#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
class Zombie{
    str::string name;
    public:
        Zombie* newZombie(std::string name);
        void randomChump(std::string name);
        Zombie(std::string name);
        void announce(void);
        ~Zombie();
};
#endif