/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:36:21 by lnicoter          #+#    #+#             */
/*   Updated: 2024/03/06 18:13:38 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_H
#define WHATEVER_H

/*
proof that i must implement the functions
that involves templates in the h file

https://cplusplus.com/forum/general/6755/

plus the subject requires the definition of the templates only in
the header files
*/
#include <iostream>

template <typename T>

void	swap(T& value1, T& value2)
{
	T	tmp = value1;

	value1 = value2;
	value2 = tmp;
}

template <typename T>

T	max(T value1, T value2)
{
	if (value1 > value2)
		return (value1);
	return (value2);
}


template <typename T>

T	min(T value1, T value2)
{
	if (value1 < value2)
		return (value1);
	return (value2);
}

#endif
