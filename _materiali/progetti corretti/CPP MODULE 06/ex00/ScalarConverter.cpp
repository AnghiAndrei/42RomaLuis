/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:31:31 by lde-mich          #+#    #+#             */
/*   Updated: 2024/02/28 16:25:01 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"


ScalarConverter::ScalarConverter()
{

}

ScalarConverter::ScalarConverter(ScalarConverter const &obj)
{
	(*this) = obj;
}

ScalarConverter::~ScalarConverter()
{

}



ScalarConverter &ScalarConverter::operator=(ScalarConverter const &obj)
{
	(void) obj;

	return (*this);
}


bool ScalarConverter::isNumber(std::string str)
{
	float floatValue;
	floatValue = std::atof(str.c_str());

	int i = -1;
	if(floatValue == std::floor(floatValue))
	{
		while(str[++i])
		{
		if ((str[i] < '0' || str[i] > '9') && (str[i] != '+' && str[i] != '-' && str[i] != '.' && str[i] != 'f'))
			{
				std::cout << "test " << str[i] << std::endl;
				return (false);
			}
		}
		return (true);
	}
	else
	{
		if ((str[str.length() - 1] >= 97 && str[str.length() - 1] <= 122) && str[str.length() - 1] != 102)
			return (false);
		while(str[++i])
			if ((str[i] < 48 || str[i] > 57) && str[i] != 102 && str[i] != 46)
				return (false);
	}

	return (true);
}


void ScalarConverter::convert(std::string str)
{
	std::stringstream ss;

	std::string specials[6] = {"-inff", "+inff", "nanf", "-inf", "+inf", "nan"};

	if (ScalarConverter::isNumber(str) == true)
	{
		int intValue;
		ss << str;
		ss >> intValue;

		float floatValue;
		floatValue = std::atof(str.c_str());

		// CHAR

		if (intValue == 0 || floatValue != std::floor(floatValue))
			std::cout << "char: non displayable" << std::endl;
		else if (intValue < 0 || intValue >= 128)
			std::cout << "char: impossible" << std::endl;
		else if (intValue < 32 || intValue == 127)
			std::cout << "char: non displayable" << std::endl;
		else
			std::cout << "char: " << "'" <<(char)intValue << "'" << std::endl;

		//____________________________________________________________
		

		//INT
		if (str.length() > 10 || (str.length() == 10 && str[str.length() - 1] > 55))
			std::cout << "int: impossible" << std::endl;
		else
			std::cout << "int: " << intValue << std::endl;
		
		//____________________________________________________________


		//FLOAT
	
		if (str.length() <= 38)
		{
			if(floatValue == std::floor(floatValue))
				std::cout << "float: " << intValue << ".0f" << std::endl;
			else
				std::cout << "float: " << floatValue<< "f" << std::endl;
		}
		else
			std::cout << "float: impossible" << std::endl;

		//____________________________________________________________


		//DOUBLE
		if (str.length() <= 308)
		{
			if(floatValue == std::floor(floatValue))
				std::cout << "double: " << intValue << ".0" << std::endl;
			else
				std::cout << "double: " << floatValue << std::endl;
		}
		else
			std::cout << "double: impossible" << std::endl;

		//____________________________________________________________
	}
	else
	{
		//SPECIALS
		for (int i = 0; i < 6; i++)
		{
			if (specials[i] == str)
			{
				std::cout << "char: impossible" << std::endl;
				std::cout << "int: impossible" << std::endl;

				if (str == specials[5] || str == specials[2])
				{
					std::cout << "float: nanf" << std::endl;
					std::cout << "double: nan" << std::endl;
				}
				else
				{
					std::cout << "float: " << specials[i] << std::endl;
					std::cout << "double: " << specials[i] << std::endl;
				}
			}
		}

		//____________________________________________________________

		if (str.length() == 1)
		{
			std::cout << "char: '" << str[0] << "'" << std::endl;
			std::cout << "int: " << static_cast<int>(str[0]) << std::endl;
			std::cout << "float: " << static_cast<float>(str[0] )<< ".0f" << std::endl;
			std::cout << "double: " << static_cast<double>(str[0]) << ".0" << std::endl;
		}
	}
}



