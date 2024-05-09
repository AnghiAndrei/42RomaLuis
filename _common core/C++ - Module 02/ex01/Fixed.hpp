#ifndef FIXED_HPP
#define FIXED_HPP
#include <string.h>
#include <iostream>
class Fixed{
    static const int bits=8;
    int nbr;
    public:
        Fixed &operator=(const Fixed &ncopy);
        void setRawBits(int const raw);
        Fixed(const Fixed &ncopy);
        Fixed(const float nbr2);
        int getRawBits() const;
        Fixed(const int nbr2);
        float toFloat() const;
        int toInt() const;
        ~Fixed();
        Fixed();
};
std::ostream &operator << (std::ostream &stream, const Fixed &fixed);
#endif