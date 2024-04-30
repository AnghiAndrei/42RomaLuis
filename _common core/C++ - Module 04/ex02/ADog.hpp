#ifndef ADOG_HPP
#define ADOG_HPP
#include "AAnimal.hpp"
class ADog : public AAnimal{
	public:
		ADog &operator=(ADog &ncopy);
		void makeSound() const;
		ADog(const ADog &ncopy);
	    ~ADog();
    	ADog();
};
#endif