#include "ClapTrap.hpp"
#include <iostream>

ClapTrap::ClapTrap(const std::string& name)
    : Name(name), HitPoints(10), EnergyPoints(10), AttackDamage(0) {
    std::cout << "ClapTrap named " << Name << " is born!" << std::endl;
}

ClapTrap::~ClapTrap() {
    std::cout << "ClapTrap named " << Name << " is destroyed!" << std::endl;
}

void ClapTrap::attack(const std::string& target) {
    if (HitPoints > 0 && EnergyPoints > 0) {
        std::cout << "ClapTrap " << Name << " attacks " << target << ", causing " << AttackDamage << " points of damage!" << std::endl;
        EnergyPoints--;
    } else {
        std::cout << "ClapTrap " << Name << " can't attack. No hit points or energy points left." << std::endl;
    }
}

void ClapTrap::takeDamage(unsigned int amount) {
    if (HitPoints > 0) {
        std::cout << "ClapTrap " << Name << " takes " << amount << " points of damage!" << std::endl;
        HitPoints -= amount;
    } else {
        std::cout << "ClapTrap " << Name << " can't take any more damage. No hit points left." << std::endl;
    }
}

void ClapTrap::beRepaired(unsigned int amount) {
    if (HitPoints > 0 && EnergyPoints > 0) {
        std::cout << "ClapTrap " << Name << " is repaired for " << amount << " hit points!" << std::endl;
        HitPoints += amount;
        EnergyPoints--;
    } else {
        std::cout << "ClapTrap " << Name << " can't be repaired. No hit points or energy points left." << std::endl;
    }
}
