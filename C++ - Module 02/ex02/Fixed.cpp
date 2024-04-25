#include "Fixed.hpp"

std::ostream &operator<<(std::ostream &stream, const Fixed &fixed){return (stream<<fixed.toFloat());}
Fixed Fixed::operator*(const Fixed &ncopy){return Fixed(this->toFloat() * ncopy.toFloat());}
Fixed Fixed::operator/(const Fixed &ncopy){return Fixed(this->toFloat() / ncopy.toFloat());}
Fixed Fixed::operator-(const Fixed &ncopy){return Fixed(this->toFloat() - ncopy.toFloat());}
Fixed Fixed::operator+(const Fixed &ncopy){return Fixed(this->toFloat() + ncopy.toFloat());}
bool Fixed::operator>=(const Fixed &ncopy) const{return (this->toFloat() >= ncopy.toFloat());}
bool Fixed::operator<=(const Fixed &ncopy) const{return (this->toFloat() <= ncopy.toFloat());}
bool Fixed::operator==(const Fixed &ncopy) const{return (this->toFloat() == ncopy.toFloat());}
bool Fixed::operator!=(const Fixed &ncopy) const{return (this->toFloat() != ncopy.toFloat());}
bool Fixed::operator>(const Fixed &ncopy) const{return (this->toFloat() > ncopy.toFloat());}
bool Fixed::operator<(const Fixed &ncopy) const{return (this->toFloat() < ncopy.toFloat());}
float Fixed::toFloat() const{return (float)this->nbr / (1<<bits);}
Fixed::Fixed(const float nbr2){this->nbr=(nbr2 * (1<<bits));}
int Fixed::toInt() const{return this->nbr >> this->bits;}
Fixed::Fixed(const Fixed &ncopy){this->nbr=ncopy.nbr;}
void Fixed::setRawBits(int const raw){this->nbr=raw;}
Fixed::Fixed(const int nbr2){this->nbr=(nbr2<<bits);}
int Fixed::getRawBits() const{return this->nbr;}
Fixed::Fixed(){this->nbr=0;}
Fixed::~Fixed(){}

Fixed &Fixed::operator=(const Fixed &ncopy){
    this->nbr=ncopy.nbr;
    return *this;
}

Fixed Fixed::operator++(int){
	Fixed nnbr;
	nnbr=*this;
	++(*this);
	return nnbr;
}

Fixed &Fixed::operator++(){
	int	nbrt;
	nbrt = this->getRawBits();
	this->setRawBits(++nbrt);
	return *this;
}

Fixed Fixed::operator--(int){
	Fixed nnbr;
	nnbr=*this;
	--(*this);
	return nnbr;
}

Fixed &Fixed::operator--(){
	int	nbrt;
	nbrt = this->getRawBits();
	this->setRawBits(--nbrt);
	return *this;
}

const Fixed& Fixed::min(const Fixed &a, const Fixed &b){
	if  (a > b)
		return b;
	return a;
}
Fixed& Fixed::min(Fixed &a, Fixed &b){
	if  (a > b)
		return b;
	return a;
}
const Fixed& Fixed::max(const Fixed &a, const Fixed &b){
	if  (a < b)
		return b;
	return a;
}
Fixed& Fixed::max(Fixed &a, Fixed &b){
	if  (a < b)
		return b;
	return a;
}