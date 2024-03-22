/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afalconi <afalconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:40:25 by afalconi          #+#    #+#             */
/*   Updated: 2024/02/08 17:57:05 by afalconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

const int	Fixed::fixed = 8;
const int	Fixed::precison = 256;

// costruttori
Fixed::Fixed()
{
	//std::cout << "Default constructor called" << std::endl;
	this->num = 0;
}

Fixed::Fixed(const int newnum)
{
	//std::cout << "Int constructor called" << std::endl;
	this->setRawBits(newnum << this->fixed);
}

Fixed::Fixed(const float newfloat)
{
	int		num;
	float	decimal;

	//std::cout << "Float constructor called" << std::endl;
	num = (int)roundf(newfloat) << this->fixed;
	decimal = newfloat - roundf(newfloat);
	num += roundf(decimal * this->precison);
	this->setRawBits(num);
}

// copy costructor
Fixed::Fixed(const Fixed &b)
{
	//std::cout << "Copy constructor called" << std::endl;
	*this = b;
}

// distruttore
Fixed::~Fixed()
{
	//std::cout << "Destructor called" << std::endl;
}

// ovdrload del operatrore =
Fixed& Fixed::operator=(const Fixed &b)
{
	//std::cout << "Copy assignment operator called" << std::endl;
	if (&b != this)
		this->setRawBits(b.getRawBits());
	return(*this);
}

// ovdrload del operatrore +
Fixed Fixed::operator+(const Fixed &b) const
{
	//std::cout << "questo e il +" << std::endl;
	return(Fixed(this->toFloat() + b.toFloat()));
}

// ovdrload del operatrore -
Fixed Fixed::operator-(const Fixed &b) const
{
	//std::cout << "questo e il -" << std::endl;
	return(Fixed(this->toFloat() -b.toFloat()));
}

// ovdrload del operatrore *
Fixed Fixed::operator*(const Fixed &b) const
{
	//std::cout << "questo e il *" << std::endl;
	return(Fixed(this->toFloat() * b.toFloat()));
}

// ovdrload del operatrore /
Fixed Fixed::operator/(const Fixed &b) const
{
	//std::cout << "questo e il /" << std::endl;
	return(Fixed(this->toFloat() / b.toFloat()));
}

// ovdrload del operatrore <
bool  Fixed::operator<(const Fixed &b) const
{
	//std::cout << "questo e il <" << std::endl;
	if (this->toFloat() < b.toFloat())
		return(true);
	return(false);

}

// ovdrload del operatrore <=
bool  Fixed::operator<=(const Fixed &b) const
{
	//std::cout << "questo e il <=" << std::endl;
	if (this->toFloat() <= b.toFloat())
		return(true);
	return(false);
}

// ovdrload del operatrore >
bool  Fixed::operator>(const Fixed &b) const
{
	//std::cout << "questo e il >" << std::endl;
	if (this->toFloat() > b.toFloat())
		return(true);
	return(false);
}

// ovdrload del operatrore >=
bool  Fixed::operator>=(const Fixed &b) const
{
	//std::cout << "questo e il >=" << std::endl;
	if (this->toFloat() >= b.toFloat())
		return(true);
	return(false);
}

// ovdrload del operatrore ==
bool  Fixed::operator==(const Fixed &b) const
{
	//std::cout << "questo e il ==" << std::endl;
	if (this->toFloat() == b.toFloat())
		return(true);
	return(false);
}

// ovdrload del operatrore !=
bool  Fixed::operator!=(const Fixed &b) const
{
	//std::cout << "questo e il !=" << std::endl;
	if (this->toFloat() != b.toFloat())
		return(true);
	return(false);
}

// ovdrload del operatrore ++ dopo del operazione
Fixed  Fixed::operator++(int)
{
	//std::cout << "questo e il ++ dopo" << std::endl;
	Fixed	ret;

	ret = *this;
	++(*this);
	return(ret);
}

// ovdrload del operatrore ++ prima del operazione
Fixed&  Fixed::operator++(void)
{
	//std::cout << "questo e il ++ prima" << std::endl;
	int	inc;
	inc = this->getRawBits();
	this->setRawBits(++inc);
	return(*this);
}

// ovdrload del operatrore -- dopo del operazione
Fixed  Fixed::operator--(int)
{
	//std::cout << "questo e il -- dopo" << std::endl;
	Fixed	ret;

	ret = *this;
	--(*this);
	return(ret);
}

// ovdrload del operatrore -- prima del operazione
Fixed&  Fixed::operator--(void)
{
	//std::cout << "questo e il -- prima" << std::endl;
	int	dec;
	dec = this->getRawBits();
	this->setRawBits(--dec);
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
	num += (float) tmp / this->precison;
	return (num);
}

int Fixed::toInt( void ) const
{
	return(this->getRawBits() >> this->fixed);
}

Fixed& Fixed::max(Fixed &a, Fixed &b)
{
	if (a > b)
		return(a);
	return(b);
}

const Fixed& Fixed::max(const Fixed &a, const Fixed &b)
{
	if (a > b)
		return(a);
	return(b);
}

Fixed& Fixed::min(Fixed &a, Fixed &b)
{
	if (a < b)
		return(a);
	return(b);
}

const Fixed& Fixed::min(const Fixed &a, const Fixed &b)
{
	if (a < b)
		return(a);
	return(b);
}

