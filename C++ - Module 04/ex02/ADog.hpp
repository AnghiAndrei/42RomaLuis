#ifndef ADOG_HPP
#define ADOG_HPP
#include "AAnimal.hpp"
class ADog : public AAnimal{
	public:
		void makeSound() const;
	    ~ADog();
    	ADog();
};
#endif