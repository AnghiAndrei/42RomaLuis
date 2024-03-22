/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:59:05 by lde-mich          #+#    #+#             */
/*   Updated: 2024/03/13 00:01:03 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"


int main ()
{
	int n = 2; // numero da cercare nel container
	std::vector<int> container1;

	container1.push_back(1);
	container1.push_back(2);
	container1.push_back(3);

	for (size_t i = 0; i < container1.size(); i++)
		std::cout << "elememt-->"<< container1[i] << std::endl;

	std::cout << "" << std::endl;

	if (::easyFind(container1, n))
		std::cout << "number:" << n << " ->found" << std::endl;
	else
		std::cout << "number:" << n << " ->not found" << std::endl;

	return (0);
}



