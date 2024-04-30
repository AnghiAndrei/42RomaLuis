#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include <string>
#include <iostream>
#include "Brain.hpp"
class Animal{
    protected:
        std::string type;
		// Brain *microb;
    public:
        Animal &operator=(Animal &ncopy);
		virtual void makeSound() const;
        std::string getType() const;
        Animal(const Animal &ncopy);
        Animal(std::string type2);
        virtual ~Animal();
        Animal();
};
#endif