/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:41:16 by lde-mich          #+#    #+#             */
/*   Updated: 2024/03/12 16:25:37 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <list>
#include <iomanip>

int main ()
{

	MutantStack<int> mstack;

	mstack.push(5);
	mstack.push(17);

	std::cout << mstack.top() << std::endl;

	mstack.pop();

	std::cout << "size-> "<< mstack.size() << std::endl;

	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//[...]
	mstack.push(0);

	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();

	++it;
	--ite;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::stack<int> s(mstack);	

	std::cout << "---------------------------------------" << std::endl;

	std::list<int> list;

	list.push_back(5);
	list.push_back(17);

	list.back();
	list.pop_back();
	list.push_back(3);

	list.push_back(5);
	list.push_back(737);
	list.push_back(0);

	MutantStack<int>::iterator itStack = mstack.begin();
	MutantStack<int>::iterator iteStack = mstack.end();
	std::list<int>::iterator itList = list.begin();
	std::list<int>::iterator iteList = list.end();

	std::cout << "\033[34m" << "Size mstack:   " << mstack.size() << "     |   Size list:   " << list.size() << std::endl;
	while ((itStack != iteStack) && (itList != iteList))
	{
		std::cout << std::setw(19) << *itStack << " | " << *itList << std::endl;
		itStack++;
		itList++;
	}
	std::cout << "\033[0m" << std::endl;

	return (0);
}

