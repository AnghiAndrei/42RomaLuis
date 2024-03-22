/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcardina <fcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:12:32 by fcardina          #+#    #+#             */
/*   Updated: 2024/02/02 15:53:46 by fcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main() {
    // Create Animal, Dog, & Cat
    const Animal* animal = new Animal();
    const Animal* dog = new Dog();
    const Animal* cat = new Cat();

	std::cout << std::endl;

    // Test getType() function
    std::cout << "Animal type: " << animal->getType() << std::endl; // Empty type
    std::cout << "Dog type: " << dog->getType() << std::endl;       // "Dog"
    std::cout << "Cat type: " << cat->getType() << std::endl;       // "Cat"

	std::cout << std::endl;

    // Test makeSound() function
    animal->makeSound(); // Default sound
    dog->makeSound();    // "Woof!"
    cat->makeSound();    // "Meow!"

	std::cout << std::endl;

    // Create instances of WrongAnimal and WrongCat
    const WrongAnimal *wrongAnimalOne = new WrongAnimal();
    const WrongAnimal *wrongAnimalTwo = new WrongCat();
    const WrongCat *wrongCat = new WrongCat();

	std::cout << std::endl;

    // Test getType() function for WrongAnimals and WrongCat
    std::cout << "WrongAnimalOne type: " << wrongAnimalOne->getType() << std::endl;
    std::cout << "WrongAnimalTwo type: " << wrongAnimalTwo->getType() << std::endl;
    std::cout << "WrongCat type: " << wrongCat->getType() << std::endl;       

	std::cout << std::endl;

    // Test makeSound() function for WrongCat
	wrongAnimalOne->makeSound();
    wrongAnimalTwo->makeSound();
    wrongCat->makeSound();

	std::cout << std::endl;

    // Clean up memory
    delete animal;
    delete cat;
    delete dog;
    delete wrongAnimalOne;
    delete wrongAnimalTwo;
    delete wrongCat;

    return (0);
}
