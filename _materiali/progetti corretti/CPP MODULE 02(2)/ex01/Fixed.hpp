/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afalconi <afalconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:41:56 by afalconi          #+#    #+#             */
/*   Updated: 2024/01/07 19:46:26 by afalconi         ###   ########.fr       */
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
	static const int	max;
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
	// ovdrload del operatrore <<
	friend std::ostream &operator<<(std::ostream &out, const Fixed &obj);
	// getter e setter vari
	int getRawBits(void) const;
	void setRawBits(int const raw);
	// metodi vari
	float toFloat( void ) const;
	int toInt( void ) const;
};

#endif
