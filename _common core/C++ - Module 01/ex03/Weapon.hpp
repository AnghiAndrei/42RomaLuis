#ifndef WEAPON_CPP
#define WEAPON_CPP
#include <string>
#include <iostream>
class Weapon{
    std::string type;
    public:
        Weapon(std::string type2);
        Weapon();
        std::string& getType();
        void setType(std::string type2);
};
#endif