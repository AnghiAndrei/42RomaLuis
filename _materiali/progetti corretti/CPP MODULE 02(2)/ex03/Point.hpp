/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afalconi <afalconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:00:45 by afalconi          #+#    #+#             */
/*   Updated: 2024/02/08 19:38:25 by afalconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP

#include <iostream>
#include <cmath>
#include "Fixed.hpp"


class Point
{
private:
	Fixed const x;
	Fixed const y;
public:
	// costruttori
	Point();
	Point(float new_x, float new_y);
	Point(const Point &p);
	// ovdrload del operatore =
	Point& operator=(const Point &p);
	// getter e setter
	const Fixed	getx();
	const Fixed	gety();
	~Point();
};

bool bsp( Point const a, Point const b, Point const c, Point const point);

#endif
