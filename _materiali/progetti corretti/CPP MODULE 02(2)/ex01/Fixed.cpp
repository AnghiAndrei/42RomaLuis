/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afalconi <afalconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:40:25 by afalconi          #+#    #+#             */
/*   Updated: 2024/01/08 16:31:53 by afalconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

const int	Fixed::fixed = 8;
const int	Fixed::max = 256;

// costruttori
Fixed::Fixed()
{
	std::cout << "Default constructor called" << std::endl;
	this->num = 0;
}

Fixed::Fixed(const int newnum)
{
	std::cout << "Int constructor called" << std::endl;
	this->setRawBits(newnum << this->fixed);
}

Fixed::Fixed(const float newfloat)
{
	int		num;
	float	decimal;

	std::cout << "Float constructor called" << std::endl;
	num = (int)roundf(newfloat) << this->fixed;
	decimal = newfloat - roundf(newfloat);
	num += roundf(decimal * this->max);
	this->setRawBits(num);
}

// copy costructor
Fixed::Fixed(const Fixed &b)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = b;
}

// distruttore
Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

// ovdrload del operatrore =
Fixed&  Fixed::operator=(const Fixed &b)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (&b != this)
		this->setRawBits(b.getRawBits());
	return(*this);
}

// ovdrload del operatrore <<
std::ostream& operator<<(std::ostream &out, const Fixed &obj)
{
	out << obj.toFloat();
	return(out);
}

// getter e setter vari
int Fixed::getRawBits(void) const
{
	return(this->num);
}

void Fixed::setRawBits(int const raw)
{
	this->num = raw;
}

// metodi vari
float Fixed::toFloat( void ) const
{
	int		tmp;
	float	num;

	tmp = this->getRawBits();
	num = tmp >> this->fixed;
	tmp -= ((int) num << this->fixed);
	num += (float) tmp / this->max;
	return (num);
}

int Fixed::toInt( void ) const
{
	return(this->getRawBits() >> this->fixed);
}
