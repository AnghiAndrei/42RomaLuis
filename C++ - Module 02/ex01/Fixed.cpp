#include "Fixed.hpp"

float Fixed::toFloat() const{return (float)this->nbr / (1<<bits);}
Fixed::~Fixed(){std::cout<<"Deconstructor called"<<std::endl;}
int Fixed::toInt() const{return this->nbr >> this->bits;}
void Fixed::setRawBits(int const raw){this->nbr=raw;}
Fixed::Fixed(){
    std::cout<<"Default constructor called"<<std::endl;
	this->nbr=0;
}

Fixed::Fixed(const int nbr2){
    std::cout<<"Int constructor called"<<std::endl;
	this->nbr=(nbr2<<bits);
}

Fixed::Fixed(const float nbr2){
	std::cout<<"Float constructor called"<<std::endl;
    this->nbr=(nbr2 * (1<<bits));
}

Fixed::Fixed(const Fixed &ncopy){
    std::cout<<"Copy constructor called"<<std::endl;
    this->nbr=ncopy.nbr;
}

Fixed &Fixed::operator=(const Fixed &ncopy){
    std::cout<<"Copy assignment operator called"<<std::endl;
    this->nbr=ncopy.nbr;
    return *this;
}

int Fixed::getRawBits() const{
    std::cout<<"getRawBits member function called"<<std::endl;
    return this->nbr;
}

std::ostream &operator<<(std::ostream &stream, const Fixed &fixed){
	stream<<fixed.toFloat();
    return (stream);
}