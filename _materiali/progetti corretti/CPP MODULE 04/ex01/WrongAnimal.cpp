/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcardina <fcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:12:38 by fcardina          #+#    #+#             */
/*   Updated: 2024/02/02 18:43:11 by fcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void)
{
	std::cout << "WRONG ANIMAL default constructor has been called" << std::endl;
};

WrongAnimal::WrongAnimal(const WrongAnimal &to_copy)
{
	*this = to_copy;
	std::cout << "WRONG ANIMAL copy constructor has been called" << std::endl;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal &to_copy)
{
	this->type = to_copy.type;
	std::cout << "WRONG ANIMAL assignment operator has been called" << std::endl;
	return *this;
}

WrongAnimal::~WrongAnimal(void)
{
	std::cout << "WRONG ANIMAL default destructor has been called" << std::endl;
}

std::string WrongAnimal::getType(void) const
{
	return this->type;
}

void WrongAnimal::setType(std::string type)
{
	this->type = type;
}

void WrongAnimal::makeSound(void) const
{
	std::cout << "WRONG ANIMAL makeSound() has been called" << std::endl;
}
