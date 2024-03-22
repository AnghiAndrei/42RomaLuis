/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:22:48 by lde-mich          #+#    #+#             */
/*   Updated: 2024/02/28 17:01:41 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

int main ()
{
	int n = 5;

	// INT--test
	std::cout << "int-arr" << std::endl;
	int arr0[5] = {1, 2, 3, 4, 5};
	::iter(arr0, n, ::ft);
	std::cout << "\n" << std::endl;
	//_________________________________

	//DOUBLE--test
	std::cout << "double-arr" << std::endl;
	double arr1[] = {1.1, 1.2, 1.3, 1.4, 1.5};
	::iter(arr1, n, ::ft);
	std::cout << "\n" << std::endl;
	//________________________________________

	//CHAR--test
	std::cout << "char-arr" << std::endl;
	char arr2[] = {'a', 'b', 'c', 'd', 'e'};
	::iter(arr2, n, ::ft);
	std::cout << "\n" << std::endl;
	//______________________________________

	//STRING-test
	std::cout << "string-arr" << std::endl;
	std::string arr3[] = {"ciao", "come", "stai", "studente", "42"};
	::iter(arr3, n, ::ft);
	std::cout << "\n" << std::endl;
	//_______________________________________________________________
	return (0);
}






