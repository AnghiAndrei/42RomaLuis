#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
int main(){
    ClapTrap bot1=ClapTrap("Stidosauro");
    ScavTrap bot2=ScavTrap("Strerizia");
    bot2.attack(bot1.getName());
    bot2.guardGate();
} 