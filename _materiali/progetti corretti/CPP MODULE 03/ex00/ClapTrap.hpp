#ifndef CLAPTRAP_H
#define CLAPTRAP_H

#include <string>

class ClapTrap {
public:
    ClapTrap(const std::string& name);
    ~ClapTrap();

    void attack(const std::string& target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);

private:
    std::string Name;
    unsigned int HitPoints;
    unsigned int EnergyPoints;
    unsigned int AttackDamage;
};

#endif
