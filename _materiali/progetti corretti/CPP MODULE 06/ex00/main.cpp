/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:16:50 by lde-mich          #+#    #+#             */
/*   Updated: 2024/02/22 11:01:44 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"


int main(int argc, char **argv)
{

	if (argc != 2)
	{
		std::cout << "Invalid input" << std::endl;
		return (0);
	}

	ScalarConverter::convert(argv[1]);

	return (0);
}




