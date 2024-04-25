#ifndef AANIMAL_HPP
#define AANIMAL_HPP
#include <string>
#include <iostream>
#include "Brain.hpp"
class AAnimal{
    protected:
        std::string type;
		Brain *microb;
    public:
        AAnimal &operator=(AAnimal &ncopy);
		virtual void makeSound() const = 0;
        std::string getType() const;
        AAnimal(const AAnimal &ncopy);
        AAnimal(std::string type2);
        virtual ~AAnimal();
        AAnimal();
};
#endif