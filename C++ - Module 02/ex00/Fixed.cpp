#include "Fixed.hpp"

Fixed::Fixed(){
    std::cout << "Default constructor called" << std::endl;
	this->nbr=0;
}

Fixed::Fixed(const Fixed &ncopy){
    std::cout << "Copy constructor called" << std::endl;
    this->nbr=ncopy.getRawBits();
}

Fixed &Fixed::operator=(const Fixed &ncopy){
    std::cout << "Copy assignment operator called" << std::endl;
    this->nbr=ncopy.getRawBits();
    return *this;
}

Fixed::~Fixed(){
    std::cout << "Deconstructor called" << std::endl;
}

int Fixed::getRawBits() const{
    std::cout << "getRawBits member function called" << std::endl;
    return nbr;
}

void Fixed::setRawBits(int const raw){
    nbr=raw;
}