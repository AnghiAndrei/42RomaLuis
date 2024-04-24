#include "FragTrap.hpp"

FragTrap::~FragTrap(){std::cout<<"Distruction FragTrap"<<std::endl;}
FragTrap::FragTrap(std::string Name2) : ClapTrap(std::string Name2){
    this->Hit_points=100;
    this->Energy_points=100;
    this->Attack_damage=30;
    std::cout<<"FragTrap "<<this->Name<<" is create!"<<std::endl;
}