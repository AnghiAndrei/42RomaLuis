/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:48:26 by lnicoter          #+#    #+#             */
/*   Updated: 2024/05/02 15:20:03 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.h"

int	main(void)
{
	int	size = 20;
	int	chunck[size];
	std::string base = "generic";
	for (int i = 0; i < size; i++)
		chunck[i] = i + 1;
	//for the function yo must always specify the type
	//seeing that they are function pointers and they don't have a defined type
	//being pointers the compiler can't recognize the type
	iter(chunck, size, call<int>);

	//example with strings
	std::string	sChunck[size];
	sChunck[0] = "jo mama";
	for (int i = 1; i < size; i++)
		sChunck[i] = sChunck[i - 1] + base;
	iter(sChunck, size, call<std::string>);
}
