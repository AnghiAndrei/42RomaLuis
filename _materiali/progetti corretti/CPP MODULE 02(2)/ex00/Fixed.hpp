/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afalconi <afalconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:41:56 by afalconi          #+#    #+#             */
/*   Updated: 2024/01/03 02:26:57 by afalconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>

class Fixed
{
private:
	int					num;
	static const int	fixed;
public:
	Fixed(void);
	Fixed(const Fixed &b);
	~Fixed();
	Fixed& operator=(const Fixed &b);
	int getRawBits(void) const;
	void setRawBits(int const raw);
};

#endif
