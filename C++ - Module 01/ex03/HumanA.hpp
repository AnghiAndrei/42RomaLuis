#ifndef HUMANA
#define HUMANA
#include <strign>
#include <iostdlib>
#include "Weapon.hpp"
class HumanA{
    std::string name;
    Weapon w;
    public:
        HumanA(std::strign name2, Weapon w2);
        void attack();
        ~HumanA();
};
#endif