#include <Fixed.hpp>

Fixed::Fixed(const int nbr2){
    this.nbr=(nbr << bits);
}

Fixed::Fixed(const float nbr2){
    this.nbr=(num * (1 << fractional_bits));
}

Fixed::~Fixed(const Fixed &copy){
    this.nbr=copy.getRawBits();
}

Fixed &Fixed::operator=(const Fixed &copy){
    this.nbr=copy.getRawBits();
    return *this;
}

Fixed::~Fixed(){
    std::cout<<"Destructor"<<std::endl;
}

int getRawBits() const{
    return this.nbr;
}

void setRawBits(int const raw){
    this.nbr=raw;
}

float toFloat() const{
    return (float)(this.nbr >> bits) + (this.nbr & ((1 << bits) - 1));
}

int toInt() const{
    return this.nbr >> bits;
}

Fixed Fixed::operator+(const Fixed &b){
    return this.toFloat() + b.toFloat();
}