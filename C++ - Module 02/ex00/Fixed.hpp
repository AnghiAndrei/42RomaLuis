#ifndef FIXED_HPP
#define FIXED_HPP
#include <string.h>
#include <iostream>
class Fixed{
    static const int bits=8;
    int nbr;
    public:
        Fixed &operator=(const Fixed &copy);
        void setRawBits(int const raw)
        Fixed(const Fixed &copy);
        int getRawBits() const;
        ~Fixed();
        Fixed();
};
#endif