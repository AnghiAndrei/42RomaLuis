/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 22:40:58 by lde-mich          #+#    #+#             */
/*   Updated: 2024/02/28 14:57:34 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

template <typename T>
void swap (T &a, T &b)
{
	T temp;

	temp = a;
	a = b;
	b = temp;
}

template <typename T>
T min (T a, T b)
{
	if (a < b)
		return (a);
	else if (a > b)
		return (b);
	else
		return (b);
}

template <typename T>
T max (T a, T b)
{
	if (a > b)
		return (a);
	else if (a < b)
		return (b);
	else
		return(b);
}






