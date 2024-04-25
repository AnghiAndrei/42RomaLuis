#include <iostream>
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
int main(){
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    const WrongAnimal* wi = new WrongCat();
    const WrongAnimal* wmeta = new WrongAnimal();
    std::cout<<j->getType()<<" "<<std::endl;
    std::cout<<i->getType()<<" "<<std::endl;
    i->makeSound();
    j->makeSound();
    meta->makeSound();
    wi->makeSound();
    wmeta->makeSound();
	delete meta;
	delete j;
	delete i;
	delete wi;
	delete wmeta;
    return 0;
}