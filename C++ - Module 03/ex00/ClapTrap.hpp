#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP
#include <string>
#include <iostream>
class ClapTrap{
    int Energy_points;
    int Attack_damage;
    std::string Name;
    int Hit_points;

    public:
        ClapTrap &operator=(const ClapTrap &copy);
        void attack(const std::string& target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
        ClapTrap(std::string Name2);
        int get_Energy_points();
        int get_Attack_damage();
        std::string get_Name();
        int get_Hit_points();
        ~ClapTrap();
};
#endif