#include <Fixed.hpp>

Fixed::Fixed(){
    std::cout<<"Default constructor"<<std::endl;
}

Fixed::~Fixed(const Fixed &copy){
    std::cout<<"Copy constructor"<<std::endl;
    this.nbr=copy.getRawBits();
}

Fixed &Fixed::operator=(const Fixed &copy){
    std::cout << "Copy assignment operator called" << std::endl;
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