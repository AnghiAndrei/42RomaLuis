#include "ClapTrap.hpp"
ClapTrap::ClapTrap(std::string Name2){
    this->Name=Name2;
    this->Hit_points=10;
    this->Energy_points=10;
    this->Attack_damage=0;
    std::cout<<"ClapTrap "<<this->Name<<" is create!"<<std::endl;
}
ClapTrap &operator=(const ClapTrap &copy){
    this->Name=copy.get_Name();
    this->Hit_points=get_Hit_points();
    this->Energy_points=get_Energy_points();
    this->Attack_damage=get_Attack_damage();
    return *this;
}
void ClapTrap::attack(const std::string& target){
    if (this->Energy_points > 0 && this->Hit_points > 0)
    {
        std::cout<<"ClapTrap "<<this->Name<<" attacks "<<target->get_Name()<<", causing "<<this->Attack_damage<<" points of damage!"<<std::endl;
        this->Energy_points-=1;
        target->takeDamage(this->Attack_damage);
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
    this->Hit_points-=amount;
    std::cout<<"ClapTrap "<<this->Name<<" lose "<<amount<<" Hp!"<<std::endl;
}
std::string ClapTrap::get_Name(){return this->Name;}
int ClapTrap::get_Hit_points(){return this->Hit_points;}
int ClapTrap::get_Energy_points(){return this->Energy_points;}
int ClapTrap::get_Attack_damage(){return this->Attack_damage;}
ClapTrap::~ClapTrap(){std::cout<<"Distruttore"<<std::endl;}