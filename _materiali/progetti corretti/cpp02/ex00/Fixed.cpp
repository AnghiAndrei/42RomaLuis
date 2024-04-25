#include "Fixed.hpp"

    Fixed::Fixed()
    {
        std::cout << "Default constructor called" << std::endl;
        fixed_point_number = 0;
    }

    Fixed::Fixed(Fixed &fixed)
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