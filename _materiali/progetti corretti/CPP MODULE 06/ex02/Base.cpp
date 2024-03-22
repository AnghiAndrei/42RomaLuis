/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:32:20 by lde-mich          #+#    #+#             */
/*   Updated: 2024/02/28 12:37:54 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "C.hpp"
#include "B.hpp"
#include "A.hpp"

Base::Base()
{

}

Base::~Base()
{

}


Base *generate(void)
{
	int random = std::rand() % 3 + 1;
	Base *obj;

	switch (random)
	{
		case 1:
			obj = new A();
			return (obj);
			break;

		case 2:
			obj = new B();
			return (obj);
			break;

		case 3:
			obj = new C();
			return (obj);
			break;
		
		default:
			return (NULL);
	}
}
	

void identify(Base *p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "*A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "*B" << std::endl;
	else if(dynamic_cast<C*>(p))
		std::cout << "*C" << std::endl;
	else
		std::cout << "Type not found" << std::endl;

}


void identify(Base &p)
{
	try
	{
		if (dynamic_cast<A*>(&p))
			std::cout << "&A" << std::endl;
		else if (dynamic_cast<B*>(&p))
			std::cout << "&B" << std::endl;
		else if(dynamic_cast<C*>(&p))
			std::cout << "&C" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Type not found" << std::endl;
	}
}











