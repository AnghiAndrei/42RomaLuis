/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:23:04 by lde-mich          #+#    #+#             */
/*   Updated: 2024/02/28 16:55:04 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>


template <typename T>
void iter (T *arr, int len, void (*ft)(T &))
{
	for (int i = 0; i < len; i++)
		ft(arr[i]);
}


template <typename T>
void ft (T element)
{
	std::cout << "element--> "<< element << std::endl;
}


