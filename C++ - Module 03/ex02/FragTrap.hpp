#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP
#include <iostream>
#include <string.h>
#include "ClapTrap.hpp"
class FragTrap : public ClapTrap{
    public:
		FragTrap &operator=(const FragTrap &ncopy);
		FragTrap(const FragTrap &ncopy);
        FragTrap(std::string Name2);
        void highFivesGuys();
        ~FragTrap();
        FragTrap();
};
#endif