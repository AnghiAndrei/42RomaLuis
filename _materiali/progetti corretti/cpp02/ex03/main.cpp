/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spiacent <spiacent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:34:19 by spiacent          #+#    #+#             */
/*   Updated: 2024/06/05 17:47:00 by spiacent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

int main ( void )
{
	if ( bsp( Point(0, 0), Point(30, 90), Point(60, 0), Point(30, 45) ) == true )
	{
		std::cout << "Point is in the triangle" << std::endl;
	}
	else
	{
		std::cout << "Point is not in the triangle" << std::endl;
	}
	return 0;
}

/*
Input: A = (0, 0), B = (30, 90), C = (60, 0), P(30, 45)
Output: Inside
Explanation:
			  B(30,90)
				/ \
			   /   \
			  /     \
			 /   P   \
			/         \
	 A(0,0) ----------- C(60,0) 

Input: A = (0, 0), B = (30, 90), C = (60, 0), P(90, 45)
Output: Outside
Explanation:
			  B(30,90)
				/ \
			   /   \
			  /     \
			 /       \      P
			/         \
	 A(0,0) ----------- C(60,0) 
*/