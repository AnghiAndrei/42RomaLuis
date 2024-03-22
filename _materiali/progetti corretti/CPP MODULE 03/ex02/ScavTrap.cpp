#include "ScavTrap.hpp"
#include <iostream>

ScavTrap::ScavTrap(const std::string& name)
    : ClapTrap(name) {
    HitPoints = 100;
    EnergyPoints = 50;
    AttackDamage = 20;
    std::cout << "ScavTrap named " << Name << " is born!" << std::endl;
}

ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap named " << Name << " is destroyed!" << std::endl;
}

void ScavTrap::guardGate() {
    std::cout << "ScavTrap " << Name << " is now in Gatekeeper mode!" << std::endl;
}
