#include "FragTrap.hpp"

void FragTrap::highFivesGuys(){std::cout<<"FragTrap "<<this->Name<<" give a High5!."<<std::endl;}
FragTrap::~FragTrap(){std::cout<<"Distruction FragTrap"<<std::endl;}
FragTrap::FragTrap(std::string Name2) : ClapTrap(Name2){
    this->Hit_points=100;
    this->Energy_points=100;
    this->Attack_damage=30;
    std::cout<<"FragTrap "<<this->Name<<" is create!"<<std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &ncopy){
	this->Name=ncopy.Name;
	this->Hit_points=ncopy.Hit_points;
    this->Energy_points=ncopy.Energy_points;
    this->Attack_damage=ncopy.Attack_damage;
	return *this;
}

FragTrap::FragTrap() : ClapTrap(){
	this->Name="";
	this->Hit_points=100;
    this->Energy_points=100;
    this->Attack_damage=30;
}

FragTrap::FragTrap(const FragTrap &ncopy) : ClapTrap(ncopy.Name){
	this->Hit_points=ncopy.Hit_points;
    this->Energy_points=ncopy.Energy_points;
    this->Attack_damage=ncopy.Attack_damage;
}