/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afalconi <afalconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:41:56 by afalconi          #+#    #+#             */
/*   Updated: 2024/01/09 17:45:40 by afalconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
# include <cmath>

class Fixed
{
private:
	int					num;
	static const int	fixed;
	static const int	precison;
public:
	// costruttori ---------------------
	Fixed();
	Fixed(const int newnum);
	Fixed(const float newfloat);
	// copy costructor
	Fixed(const Fixed &b);
	// distruttore
	~Fixed();
	// ovdrload del operatrore =
	Fixed& operator=(const Fixed &b);
	// ovdrload del operatrore +
	Fixed operator+(const Fixed &b) const;
	// ovdrload del operatrore -
	Fixed operator-(const Fixed &b) const;
	// ovdrload del operatrore *
	Fixed operator*(const Fixed &b) const;
	// ovdrload del operatrore /
	Fixed operator/(const Fixed &b) const;
	// ovdrload del operatrore >
	bool operator>(const Fixed &b) const;
	// ovdrload del operatrore <
	bool operator<(const Fixed &b) const;
	// ovdrload del operatrore >=
	bool operator>=(const Fixed &b) const;
	// ovdrload del operatrore <=
	bool operator<=(const Fixed &b) const;
	// ovdrload del operatrore ==
	bool operator==(const Fixed &b) const;
	// ovdrload del operatrore !=
	bool operator!=(const Fixed &b) const;
	// ovdrload del operatrore ++ dopo del operazione
	Fixed  operator++(int);
	// ovdrload del operatrore ++ prima del operazione
	Fixed&  operator++(void);
	// ovdrload del operatrore -- dopo del operazione
	Fixed  operator--(int);
	// ovdrload del operatrore -- prima del operazione
	Fixed&  operator--(void);
	// ovdrload del operatrore <<
	friend std::ostream &operator<<(std::ostream &out, const Fixed &obj);
	// getter e setter vari
	int getRawBits(void) const;
	void setRawBits(int const raw);
	// metodi vari
	float toFloat( void ) const;
	int toInt( void ) const;
	static Fixed& max(Fixed &a, Fixed &b);
	static const Fixed& max(const Fixed &a, const Fixed &b);
	static Fixed& min(Fixed &a, Fixed &b);
	static const Fixed& min(const Fixed &a, const Fixed &b);
};

#endif
