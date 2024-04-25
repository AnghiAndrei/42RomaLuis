#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed
{
private:
        int fixed_point_number;
        static const int bits = 8;
public:
        Fixed();
        Fixed(const int);
        Fixed(const float);
        Fixed(const Fixed &fixed);
        int toInt( void ) const;
        float toFloat( void ) const;
        Fixed & operator = (const Fixed &fixed);
        ~Fixed();
        int getRawBits( void ) const;
        void setRawBits( int const raw );
        friend std::ostream &operator << (std::ostream &stream, const Fixed &fixed);
};

#endif