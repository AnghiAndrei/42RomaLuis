#include "ScavTrap.hpp"
void ScavTrap::guardGate(){cout<<"ScavTrap "<<this->Name<<"is now in Gate keeper mode."<<std::endl;}
ScavTrap::~ScavTrap(){std::cout<<"Distruction ScavTrap"<<std::endl;}
ScavTrap::ScavTrap(std::string Name2) : ClapTrap(name){
    this->Hit_points=100;
    this->Energy_points=50;
    this->Attack_damage=20;
    std::cout<<"ScavTrap "<<this->Name<<" is create!"<<std::endl;
}
void ScavTrap::attack(const std::string& target){
    if (this->Energy_points > 0 && this->Hit_points > 0)
    {
        std::cout<<"ClapTrap "<<this->Name<<" attacks "<<target->get_Name()<<", causing "<<this->Attack_damage<<" points of damage!"<<std::endl;
        this->Energy_points-=1;
        target->takeDamage(this->Attack_damage);
    }
}