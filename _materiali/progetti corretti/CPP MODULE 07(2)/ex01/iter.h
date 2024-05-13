/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:01:06 by lnicoter          #+#    #+#             */
/*   Updated: 2024/05/02 15:23:35 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_H
#define ITER_H

#include <iostream>

template <typename T, typename Func>
void	iter(T *array, int size, Func func)
{
	for (int i = 0; i < size; i++)
		func(array[i]);
}

template <typename T>
void	call(T arrayValue)
{
	std::cout<<"value of the array "<<arrayValue<<std::endl;
}

/*
is amazing i can transform the functions in templates
and then call them just like that, and if a function corresponds
at the number of arguments that i have passed, and i the main
when i call iter i'm passing as an argument the function call so the template
will automatically adapt

*/
#endif
