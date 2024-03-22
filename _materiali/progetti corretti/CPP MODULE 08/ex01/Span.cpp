/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:12:54 by lde-mich          #+#    #+#             */
/*   Updated: 2024/03/07 18:19:51 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"


Span::Span()
{

}

Span::Span(Span const &obj)
{
	(*this) = obj;
}

Span::Span(unsigned int n)
{
	this->size = n;
    this->container.resize(this->size, 0);
}

Span::~Span()
{

}


Span &Span::operator=(Span const &obj)
{
	if (this == &obj)
		return (*this);

	this->container = obj.container;
	this->size = obj.size;

	return (*this);
}


unsigned int const &Span::getSize() const
{
	return (this->size);
}


void Span::addNumber(unsigned int n)
{
	for (unsigned int i = 0; i < this->size; i++)
	{	
		if (this->container[i] == 0)
		{
			this->container[i] = n;
			return ;
		}
	}

	throw Span::MemoryFullException();
}

void Span::addMoreNumber()
{
	std::srand(std::time(0));
	unsigned int i = 0;

	for (std::vector<unsigned int>::iterator it = this->container.begin(); it < this->container.end() && i < this->size; it++, i++)
	{
		if (*it == 0)
			*it = std::rand() % 1000 + 1;
	}
}

unsigned int Span::shortestSpan()
{	
	if (this->size <= 1)
		throw Span::NumberStoredException();

	std::vector<unsigned int> newContainer;
	newContainer = this->container;

	std::sort(newContainer.begin(), newContainer.end());
	std::adjacent_difference(newContainer.begin(), newContainer.end(), newContainer.begin());

	std::vector<unsigned int>::iterator diff;
	diff = std::min_element(newContainer.begin(), newContainer.end());

	return (*diff);
	
}

unsigned int Span::longestSpan()
{
	if (this->size <= 1)
		throw Span::NumberStoredException();

	std::vector<unsigned int>::iterator maxElement;
	maxElement = std::max_element(this->container.begin(), this->container.end());

	std::vector<unsigned int>::iterator minElement;
	minElement = std::min_element(this->container.begin(), this->container.end());

	return (*maxElement - *minElement);	
}









