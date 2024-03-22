/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:22:16 by lde-mich          #+#    #+#             */
/*   Updated: 2024/02/27 13:49:35 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <stdint.h>

typedef struct Data
{
	std::string str;

}	Data;

class Serializer
							{
	private:

		Serializer operator=(Serializer const &obj);
		Serializer(Serializer const &obj);
		Serializer();
		~Serializer();

	public:

		static uintptr_t serialize(Data* ptr);
		static Data* deserialize(uintptr_t raw);

};
