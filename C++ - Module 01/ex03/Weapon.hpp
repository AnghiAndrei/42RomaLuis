#ifndef WEAPON_CPP
#define WEAPON_CPP
#include <strign>
#include <iostdlib>
class Weapon{
    std::string type;
    public:
        Weapon(std::string type2);
        std::string getType();
        void setType(std::string type2);
        ~Weapon();
};
#endif