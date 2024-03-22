#include "FragTrap.hpp"
#include <iostream>

FragTrap::FragTrap(const std::string& name)
    : ClapTrap(name) {
    HitPoints = 100;
    EnergyPoints = 100;
    AttackDamage = 30;
    std::cout << "FragTrap named " << Name << " is born!" << std::endl;
}

FragTrap::~FragTrap() {
    std::cout << "FragTrap named " << Name << " is destroyed!" << std::endl;
}

void FragTrap::highFivesGuys() {
    std::cout << "FragTrap " << Name << " requests a high five from everyone!" << std::endl;
}
