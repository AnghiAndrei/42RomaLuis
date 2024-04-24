#ifndef HUMANA_HPP
#define HUMANA_HPP
#include <string>
#include <iostream>
#include "Weapon.hpp"
class Weapon;
class HumanA{
    std::string name;
    Weapon w;
    public:
        HumanA(std::string name2, Weapon &w2);
        void attack();
};
#endif