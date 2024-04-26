#include "ScavTrap.hpp"
void ScavTrap::guardGate(){std::cout<<"ScavTrap "<<this->Name<<"is now in Gate keeper mode."<<std::endl;}
ScavTrap::~ScavTrap(){std::cout<<"Distruction ScavTrap"<<std::endl;}
ScavTrap::ScavTrap(std::string Name2) : ClapTrap(Name2){
    this->Hit_points=100;
    this->Energy_points=50;
    this->Attack_damage=20;
    std::cout<<"ScavTrap "<<this->Name<<" is create!"<<std::endl;
}

void ScavTrap::attack(const std::string& target){
    if (this->Energy_points > 0 && this->Hit_points > 0)
    {
        std::cout<<"ClapTrap "<<this->Name<<" attacks "<<target<<", causing "<<this->Attack_damage<<" points of damage!"<<std::endl;
        this->Energy_points-=1;
    }
}

ScavTrap &ScavTrap::operator=(const ScavTrap &ncopy){
	this->Name=ncopy.Name;
	this->Hit_points=ncopy.Hit_points;
    this->Energy_points=ncopy.Energy_points;
    this->Attack_damage=ncopy.Attack_damage;
	return *this;
}

ScavTrap::ScavTrap(){
	this->Name="";
	this->Hit_points=0;
    this->Energy_points=0;
    this->Attack_damage=0;
}

ScavTrap::ScavTrap(const ScavTrap &ncopy) : ClapTrap(ncopy.Name){
	this->Hit_points=ncopy.Hit_points;
    this->Energy_points=ncopy.Energy_points;
    this->Attack_damage=ncopy.Attack_damage;
}