#ifndef CAT_HPP
#define CAT_HPP
#include "Animal.hpp"
class Cat : public Animal{
	Brain *microb;
	public:
		Cat &operator=(Cat &ncopy);
		void makeSound() const;
		Cat(const Cat &ncopy);
	    ~Cat();
    	Cat();
};
#endif