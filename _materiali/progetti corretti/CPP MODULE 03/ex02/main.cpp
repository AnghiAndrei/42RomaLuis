#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main() {
    ClapTrap claptrap("CL4P-TP");
    claptrap.attack("Enemy1");
    claptrap.takeDamage(5);
    claptrap.beRepaired(3);

    ScavTrap scavtrap("SC4V-TP");
    scavtrap.attack("Enemy2");
    scavtrap.takeDamage(15);
    scavtrap.beRepaired(8);
    scavtrap.guardGate();  

    FragTrap fragtrap("FR4G-TP");
    fragtrap.attack("Enemy3");
    fragtrap.takeDamage(20);
    fragtrap.beRepaired(10);
    fragtrap.highFivesGuys();

    return 0;
}
