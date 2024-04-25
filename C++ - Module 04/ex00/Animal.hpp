#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include <string>
#include <iostream>
class Animal{
    protected:
        std::string type;
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