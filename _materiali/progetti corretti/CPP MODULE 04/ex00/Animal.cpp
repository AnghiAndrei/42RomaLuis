/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcardina <fcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:11:30 by fcardina          #+#    #+#             */
/*   Updated: 2024/02/06 03:16:15 by fcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Animal.hpp"

Animal::Animal(void)
{
	std::cout << "ANIMAL default constructor has been called" << std::endl;
};

Animal::Animal(const Animal &to_copy)
{
	*this = to_copy;
	std::cout << "ANIMAL copy constructor has been called" << std::endl;
}

Animal& Animal::operator=(const Animal &to_copy)
{
	this->type = to_copy.type;
	std::cout << "ANIMAL assignment operator has been called" << std::endl;
	return *this;
}

Animal::~Animal(void)
{
	std::cout << "ANIMAL default destructor has been called" << std::endl;
}

std::string Animal::getType(void) const
{
	return this->type;
}

void Animal::setType(std::string type)
{
	this->type = type;
}

void Animal::makeSound(void) const
{
	std::cout << "ANIMAL makeSound() has been called" << std::endl;
}
