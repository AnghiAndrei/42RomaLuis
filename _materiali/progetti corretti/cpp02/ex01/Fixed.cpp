#include "Fixed.hpp"

Fixed::Fixed()
{
    std::cout << "Default constructor called" << std::endl;
    fixed_point_number = 0;
}

Fixed::Fixed(const int num)
{
    fixed_point_number = num * (1 << bits);
	std::cout << "Int constructor called" << std::endl;
}

int Fixed::toInt( void ) const
{
    return ((int) fixed_point_number / (1 << bits));
}

float Fixed::toFloat( void ) const
{
    return ((float) fixed_point_number / (1 << bits));
}

Fixed::Fixed(const float num)
{
    fixed_point_number = num * (1 << bits);
	std::cout << "Float constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &fixed)
{
    std::cout << "Copy constructor called" << std::endl;
    this->fixed_point_number = fixed.fixed_point_number;
}

Fixed & Fixed::operator = (const Fixed &fixed)
{
    std::cout << "Copy assignment operator called" << std::endl;
    fixed_point_number = fixed.fixed_point_number;
    return *this;
}

std::ostream &operator << (std::ostream &stream, const Fixed &fixed)
{
    stream << fixed.toFloat();
    return (stream);
}

Fixed::~Fixed()
{
    std::cout << "Deconstructor called" << std::endl;
}

int Fixed::getRawBits( void ) const
{
    std::cout << "getRawBits member function called" << std::endl;
    return fixed_point_number;
}

void Fixed::setRawBits( int const raw )
{
    fixed_point_number = raw;
}