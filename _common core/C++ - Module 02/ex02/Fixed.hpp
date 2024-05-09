#ifndef FIXED_HPP
#define FIXED_HPP
#include <string.h>
#include <iostream>
class Fixed{
    static const int bits=8;
    int nbr;
    public:
		static const Fixed& min(const Fixed &a, const Fixed &b);
		static const Fixed& max(const Fixed &a, const Fixed &b);
        bool operator>=(const Fixed &ncopy) const;
        bool operator<=(const Fixed &ncopy) const;
        bool operator==(const Fixed &ncopy) const;
        bool operator!=(const Fixed &ncopy) const;
        bool operator>(const Fixed &ncopy) const;
        bool operator<(const Fixed &ncopy) const;
		static Fixed& max(Fixed &a, Fixed &b);
		static Fixed& min(Fixed &a, Fixed &b);
        Fixed &operator=(const Fixed &ncopy);
		Fixed operator*(const Fixed &ncopy);
		Fixed operator/(const Fixed &ncopy);
		Fixed operator-(const Fixed &ncopy);
		Fixed operator+(const Fixed &ncopy);
        void setRawBits(int const raw);
        Fixed(const Fixed &ncopy);
        Fixed(const float nbr2);
        int getRawBits() const;
        Fixed(const int nbr2);
        float toFloat() const;
		Fixed operator++(int);
		Fixed operator--(int);
		Fixed &operator++();
		Fixed &operator--();
        int toInt() const;
        ~Fixed();
        Fixed();
};
std::ostream &operator<<(std::ostream &stream, const Fixed &fixed);
#endif