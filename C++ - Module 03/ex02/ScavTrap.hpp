#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP
class ScavTrap : public ClapTrap{
    public:
        void attack(const std::string& target);
        ScavTrap(std::string Name2);
        void guardGate();
        ~ScavTrap();
};
#endif