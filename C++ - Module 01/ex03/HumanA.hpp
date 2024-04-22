#ifndef HUMANA
#define HUMANA
#include <string>
#include <iostream>
#include "Weapon.hpp"
class HumanA{
    std::string name;
    Weapon w;
    public:
        HumanA(std::string name2, Weapon w2);
        void attack();
};
#endif