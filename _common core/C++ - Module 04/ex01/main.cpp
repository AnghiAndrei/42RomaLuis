#include <iostream>
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
int main(){
    // const Animal* j = new Dog();
    // const Animal* i = new Cat();
	// delete j;
	// delete i;
	Dog basic;
	basic.makeSound();
	{
		Dog tmp = basic;
	}
    return 0;
}