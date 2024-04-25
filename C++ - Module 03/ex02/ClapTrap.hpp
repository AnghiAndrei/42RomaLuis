#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP
#include <iostream>
#include <string.h>
class ClapTrap{
	protected:
		int Energy_points;
		int Attack_damage;
		std::string Name;
		int Hit_points;

    public:
        ClapTrap &operator=(const ClapTrap &ncopy);
        void attack(const std::string& target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
		ClapTrap(const ClapTrap &ncopy);
        ClapTrap(std::string Name2);
		std::string getName();
        ~ClapTrap();
};
#endif