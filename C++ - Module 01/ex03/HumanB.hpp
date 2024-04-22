#ifndef HUMANB
#define HUMANB
#include <string>
#include <iostream>
#include "Weapon.hpp"
class HumanB{
    std::string name;
    Weapon w;
    public:
        HumanB(std::string name2);
        void setWeapon(Weapon w2);
        void attack();
};
#endif