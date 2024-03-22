/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afalconi <afalconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:00:40 by afalconi          #+#    #+#             */
/*   Updated: 2024/02/08 19:44:36 by afalconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point(): x(Fixed(0)), y(Fixed(0))
{

}

Point::Point(float new_x, float new_y): x(Fixed(new_x)), y(Fixed(new_y))
{

}

Point::Point(const Point &p)
{
	*this = p;
}

Point::~Point()
{

}

Point& Point::operator=(const Point &p)
{
	*this = Point(p.x.getRawBits(), p.y.getRawBits());
}

const Fixed Point::getx()
{
	return(this->x);
}

const Fixed Point::gety()
{
	return(this->y);
}
