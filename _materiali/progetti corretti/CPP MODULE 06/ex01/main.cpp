/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:45:10 by lde-mich          #+#    #+#             */
/*   Updated: 2024/02/27 12:12:17 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int main ()
{
	Data *ptr = new Data;
	Data *new_ptr;
	uintptr_t	raw;

	ptr->str = "Hello world";

	raw = Serializer::serialize(ptr);
	new_ptr = Serializer::deserialize(raw);

	std::cout << "ptr--> " << ptr << std::endl;
	std::cout << "new_ptr--> " << new_ptr << std::endl;

	return (0);
}

