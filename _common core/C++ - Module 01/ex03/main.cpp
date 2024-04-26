#include "HumanA.hpp"
#include "HumanB.hpp"
int main(){
    {
        Weapon club = Weapon("Style Nico");
        HumanA bob("Hooma", club);
        bob.attack();
        club.setType("Box");
        bob.attack();
    }
    {
        Weapon club = Weapon("Karate");
        HumanB jim("Baki");
        jim.setWeapon(club);
        jim.attack();
        club.setType("Wresling");
        jim.attack();
    }
    return 0;
}