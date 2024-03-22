/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:58:31 by lde-mich          #+#    #+#             */
/*   Updated: 2024/03/13 00:00:14 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
bool easyFind(T container, int num)
{
	std::vector<int>::iterator it;

	 it = find(container.begin(), container.end() , num);

	 if (it != container.end())
		 return (true);
	 else
		 return (false);
}


