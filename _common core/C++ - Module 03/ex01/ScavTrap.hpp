#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP
#include "ClapTrap.hpp"
class ScavTrap : public ClapTrap{
    public:
		ScavTrap &operator=(const ScavTrap &ncopy);
        void attack(const std::string& target);
        ScavTrap(const ScavTrap &ncopy);
        ScavTrap(std::string Name2);
        void guardGate();
        ~ScavTrap();
        ScavTrap();
};
#endif