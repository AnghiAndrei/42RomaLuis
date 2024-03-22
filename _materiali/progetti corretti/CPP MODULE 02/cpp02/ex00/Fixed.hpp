#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <string>
#include <cmath>

class Fixed
{
    private:
        int value;
        static const int fraction_bits = 8;

    public:
        Fixed();
        /*declare a cp construcor for the fixed class that
         init a new object : init list the member value
         of the current object*/
        Fixed(const Fixed& other);//reference to the object being copied
        ~Fixed();
        Fixed &operator=(const Fixed &other);
        int getRawBits(void) const;
        void setRawBits(int const rawBit);
};

#endif