#include "Fixed.hpp"

Fixed::Fixed() : value(0){
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &other)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = other;

}

Fixed &Fixed::operator=(const Fixed &other){
    std::cout << "Copy assignment operator called" << std::endl;
    this->setRawBits(other.getRawBits());
    return (*this);
}

Fixed::~Fixed(){
    std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits() const{
    return (value);

}

void Fixed::setRawBits(int const rawBit){
    this->value = rawBit;
}

Fixed::Fixed(const int integer)
{
	std::cout << "Int constructor called" << std::endl;
	this->value = (integer << Fixed::fraction_bits);
}

Fixed::Fixed(const float floating_point)
{
	std::cout << "Float constructor called" << std::endl;
	this->value = roundf(floating_point * (1 << Fixed::fraction_bits));
	//Transforming a floating-point number into a fixed-point number by scaling it according to the number of fractional bits (_bits), rounding the result, and then storing it in an integer member variable (_RawBits).
}

float Fixed::toFloat(void) const
{
	return ((float)this->value / (float)(1 << Fixed::fraction_bits));
}

int	Fixed::toInt(void) const
{
	return (this->value >> Fixed::fraction_bits);
}

std::ostream &operator<<(std::ostream &stream, Fixed const &f)
{
	stream << f.toFloat();
	return (stream);
}

