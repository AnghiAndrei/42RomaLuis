/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcardina <fcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:13:11 by fcardina          #+#    #+#             */
/*   Updated: 2024/02/06 19:55:46 by fcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>
#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "Brain.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
    // Create an array of Animal pointers
    const int numAnimals = 8;
    Animal *animals[numAnimals];
    int dogCount = 0;
    int catCount = 0;

    // Fill the array with half Dog and half Cat objects
    for (int i = 0; i < numAnimals; i++)
    {
        if (i < numAnimals / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }

    for (int i = 0; i < numAnimals; i++)
    {
        Animal *animal = animals[i];
        if (animal->getType() == "Dog")
        {
            dogCount++;
            std::cout << "Dog n°" << dogCount << " says: ";
            animals[i]->makeSound();
        }
        else if (animal->getType() == "Cat")
        {
            catCount++;
            std::cout << "Cat n°" << catCount << " says: ";
            animals[i]->makeSound();
        }
    }
    std::cout << std::endl;

    // Delete the original animals and their brains
    for (int i = 0; i < numAnimals; i++)
    {
        delete animals[i];
    }
    std::cout << std::endl;

    // Testing for Dog deep copy
    Dog *deepDog = new Dog();
    std::cout << std::endl;

    Dog *dogCopy = new Dog(*deepDog);  // Create a copy
    //std::cout << "Original Dog's Idea: " << deepDog->getBrain()->getIdea(0) << std::endl;
    dogCopy->getBrain()->setIdea(0, "New Dog Idea 0");  // Modify the copy
    dogCopy->getBrain()->setIdea(1, "New Dog Idea 1");
    dogCopy->getBrain()->setIdea(2, "New Dog Idea 2");
    dogCopy->getBrain()->setIdea(3, "New Dog Idea 3");
    dogCopy->getBrain()->setIdea(4, "New Dog Idea ...");

    dogCopy->getIdea();
    std::cout << std::endl;



    // Testing for Cat deep copy
    Cat *deepCat = new Cat();
    std::cout << std::endl;

    Cat *catCopy = new Cat(*deepCat);  // Create a copy
    //std::cout << "Original Cat's Idea: " << deepCat->getBrain()->getIdea(0) << std::endl;
    catCopy->getBrain()->setIdea(0, "New Cat Idea 0");  // Modify the copy
    catCopy->getBrain()->setIdea(1, "New Cat Idea 1");
    catCopy->getBrain()->setIdea(2, "New Cat Idea 2");
    catCopy->getBrain()->setIdea(3, "New Cat Idea 3");
    catCopy->getBrain()->setIdea(4, "New Cat Idea ...");
    
    catCopy->getIdea();
    std::cout << std::endl;

    delete deepDog;
    delete dogCopy;
    delete deepCat;
    delete catCopy;

    return (0);
}