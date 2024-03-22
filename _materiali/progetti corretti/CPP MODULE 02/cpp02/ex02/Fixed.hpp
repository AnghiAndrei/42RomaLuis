#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed {
private:
    int value; // An integer to store the fixed-point number value
    static const int fraction_bits = 8; // Number of fractional bits

public:
    Fixed(); // Default constructor
    Fixed(const Fixed &other); // Copy constructor
    Fixed &operator=(const Fixed &other); // Copy assignment operator
    ~Fixed(); // Destructor
    int getRawBits() const; // Method to get the raw bits
    void setRawBits(int const rawBit); // Method to set the raw bits
    Fixed(const int integer); // Constructor from integer
    Fixed(const float floating_point); // Constructor from float
    float toFloat() const; // Method to convert to float
    friend std::ostream &operator<<(std::ostream &stream, const Fixed &f); // Overloaded output stream operator
    Fixed operator+(const Fixed &f) const; // Arithmetic operators
    Fixed operator-(const Fixed &f) const;
    Fixed operator*(const Fixed &f) const;
    Fixed operator/(const Fixed &f) const;
    bool operator>(const Fixed &f) const; // Comparison operators
    bool operator<(const Fixed &f) const;
    bool operator>=(const Fixed &f) const;
    bool operator<=(const Fixed &f) const;
    bool operator==(const Fixed &f) const;
    bool operator!=(const Fixed &f) const;
    Fixed &operator++(); // Increment and decrement operators
    Fixed operator++(int);
    Fixed &operator--();
    Fixed operator--(int);
    static const Fixed &min(const Fixed &a, const Fixed &b); // Static min and max functions
    static const Fixed &max(const Fixed &a, const Fixed &b);
};

#endif // FIXED_H

