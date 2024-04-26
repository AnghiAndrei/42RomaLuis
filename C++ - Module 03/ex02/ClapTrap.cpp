#include "ClapTrap.hpp"

ClapTrap::~ClapTrap(){std::cout<<"ClapTrap "<<this->Name<<" died!"<<std::endl;}
std::string ClapTrap::getName(){return this->Name;}
ClapTrap::ClapTrap(std::string Name2){
    this->Name=Name2;
    this->Hit_points=10;
    this->Energy_points=10;
    this->Attack_damage=0;
    std::cout<<"ClapTrap "<<this->Name<<" is create!"<<std::endl;
}

ClapTrap::ClapTrap(){
	this->Name="";
	this->Hit_points=10;
    this->Energy_points=10;
    this->Attack_damage=0;
}

ClapTrap::ClapTrap(const ClapTrap &ncopy){
    this->Name=ncopy.Name;
    this->Hit_points=ncopy.Hit_points;
    this->Energy_points=ncopy.Energy_points;
    this->Attack_damage=ncopy.Attack_damage;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &ncopy){
    this->Name=ncopy.Name;
    this->Hit_points=ncopy.Hit_points;
    this->Energy_points=ncopy.Energy_points;
    this->Attack_damage=ncopy.Attack_damage;
    return *this;
}

void ClapTrap::attack(const std::string &target){
    if (this->Energy_points > 0 && this->Hit_points > 0)
    {
        std::cout<<"ClapTrap "<<this->Name<<" attacks "<<target<<", causing "<<this->Attack_damage<<" points of damage!"<<std::endl;
        this->Energy_points-=1;
    }
}

void ClapTrap::beRepaired(unsigned int amount){
    if (this->Energy_points > 0 && this->Hit_points > 0)
    {
        this->Energy_points-=1;
        this->Hit_points+=amount;
        std::cout<<"ClapTrap "<<this->Name<<" is repaired to "<<this->Hit_points<<" Hp!"<<std::endl;
    }
}

void ClapTrap::takeDamage(unsigned int amount){
	if (this->Hit_points > 0){
		this->Hit_points-=amount;
		std::cout<<"ClapTrap "<<this->Name<<" lose "<<amount<<" Hp!"<<std::endl;
	}
}