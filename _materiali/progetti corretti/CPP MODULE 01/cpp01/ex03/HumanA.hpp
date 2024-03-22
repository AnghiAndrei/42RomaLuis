#ifndef HUMANA_HPP
#define HUMANA_HPP

#include <iostream>
#include <string>
#include "Weapon.hpp"

class Weapon;

class HumanA
{
    private:
        std::string _name; // name of human A
        Weapon _weapon; //reference to Weapon object
    public:
        HumanA(std::string name, Weapon &weapon);
        ~HumanA(void);
        void attack();

};

#endif
