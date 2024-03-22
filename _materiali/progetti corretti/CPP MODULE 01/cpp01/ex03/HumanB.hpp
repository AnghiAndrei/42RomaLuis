#ifndef HUMANB_HPP
#define HUMANB_HPP

#include <iostream>
#include <string>
#include "Weapon.hpp"

class HumanB
{
    private:
        std::string _name;
        Weapon *_weapon;  // Use a pointer to Weapon

    public:
        HumanB(std::string name);
        ~HumanB(void);

        void attack(void);
        void setWeapon(Weapon &weapon);  // Set weapon using a pointer
};

#endif
