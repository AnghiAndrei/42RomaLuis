#include "ClapTrap.hpp"

int main() {
    ClapTrap claptrap("CL4P-TP");

    claptrap.attack("Enemy1");
    claptrap.takeDamage(5);
    claptrap.beRepaired(3);

    return 0;
}
