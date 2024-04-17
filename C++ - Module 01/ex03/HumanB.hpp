#ifndef HUMANB
#define HUMANB
#include <strign>
#include <iostdlib>
#include "Weapon.hpp"
class HumanB{
    std::string name;
    Weapon w;
    public:
        HumanB(std::strign name2);
        void setWeapon(Weapon w2);
        void attack();
        ~HumanB();
};
#endif