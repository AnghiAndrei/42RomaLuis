#include "Fixed.hpp"

// Default constructor
Fixed::Fixed() : value(0) {}

// Copy constructor
Fixed::Fixed(const Fixed &other) {
    *this = other;
}

// Copy assignment operator
Fixed &Fixed::operator=(const Fixed &other) {
    this->value = other.getRawBits();
    return (*this);
}

// Destructor
Fixed::~Fixed() {}

// Method to get the raw bits
int Fixed::getRawBits() const {
    return value;
}

// Method to set the raw bits
void Fixed::setRawBits(int const rawBit) {
    value = rawBit;
}

// Constructor from integer
Fixed::Fixed(const int integer) {
    this->value = integer << fraction_bits;
}

// Constructor from float
Fixed::Fixed(const float floating_point) {
    this->value = roundf(floating_point * (1 << fraction_bits));
}

// Method to convert to float
float Fixed::toFloat() const {
    return static_cast<float>(value) / (1 << fraction_bits);
}

// Overloaded output stream operator
std::ostream &operator<<(std::ostream &stream, const Fixed &f) {
    stream << f.toFloat();
    return stream;
}

// Arithmetic operators
Fixed Fixed::operator+(const Fixed &f) const {
    Fixed result;
    result.setRawBits(value + f.getRawBits());
    return result;
}

Fixed Fixed::operator-(const Fixed &f) const {
    Fixed result;
    result.setRawBits(value - f.getRawBits());
    return result;
}

Fixed Fixed::operator*(const Fixed &f) const {
    Fixed result;
    result.setRawBits((value * f.getRawBits()) >> fraction_bits);
    return result;
}

Fixed Fixed::operator/(const Fixed &f) const {
    Fixed result;
    result.setRawBits((value << fraction_bits) / f.getRawBits());
    return result;
}

// Comparison operators
bool Fixed::operator>(const Fixed &f) const {
    return value > f.getRawBits();
}

bool Fixed::operator<(const Fixed &f) const {
    return value < f.getRawBits();
}

bool Fixed::operator>=(const Fixed &f) const {
    return value >= f.getRawBits();
}

bool Fixed::operator<=(const Fixed &f) const {
    return value <= f.getRawBits();
}

bool Fixed::operator==(const Fixed &f) const {
    return value == f.getRawBits();
}

bool Fixed::operator!=(const Fixed &f) const {
    return value != f.getRawBits();
}

// Increment and decrement operators
Fixed &Fixed::operator++() { // Pre-increment
    ++value;
    return *this;
}

Fixed Fixed::operator++(int) { // Post-increment
    Fixed temp(*this);
    ++value;
    return temp;
}

Fixed &Fixed::operator--() { // Pre-decrement
    --value;
    return *this;
}

Fixed Fixed::operator--(int) { // Post-decrement
    Fixed temp(*this);
    --value;
    return temp;
}

// Static min and max functions
const Fixed &Fixed::min(const Fixed &a, const Fixed &b) {
    return (a < b) ? a : b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
    return (a > b) ? a : b;
}
