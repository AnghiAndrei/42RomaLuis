#ifndef DOG_HPP
#define DOG_HPP
#include "Animal.hpp"
class Dog : public Animal{
	Brain *microb;
	public:
		Dog &operator=(Dog &ncopy);
		void makeSound() const;
		Dog(const Dog &ncopy);
	    ~Dog();
    	Dog();
};
#endif