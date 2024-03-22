/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:23:34 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/01/21 16:54:26 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

void PhoneBook::addContact() {

	static int  index = -1;

	if (++index < 8)
		contacts[index].createContact();
	else
	{
		index = 0;
		contacts[index].createContact();
	}
	return ;
}

void PhoneBook::searchContact(int count) {

	printList(count);
	std::cout << "\nScegli index da visualizzare\n- > ";

	std::string input;
	
	std::getline(std::cin, input);
	int index = input[0] - 48;

	if (index < 1 || index > count || input.size() > 1)
		std::cout << "\nError: index out of range.\n\n";
	else if (index > 0 && index < 9 && index <= count)
		std::cout << contacts[index - 1].toString() << std::endl;
	return ;
}

void PhoneBook::printList(int count) {
	
	std::cout << "-------------------------------------------------------" << std::endl;
	std::cout << " |         id |  firstname |   lastname |   nickname |\n" << std::endl;
	std::cout << "-------------------------------------------------------" << std::endl;
	for (int i = 0; i < count; ++i)
		std::cout << " |          " << (i + 1) << " | " << resizeValue(contacts[i].getFirstName()) << " | "
				  << resizeValue(contacts[i].getLastName()) << " | "
				  << resizeValue(contacts[i].getNickName()) << " |\n";
	std::cout << "-------------------------------------------------------" << std::endl;
	return ;
}

std::string PhoneBook::resizeValue(std::string s) {

	if (s.length() > 10) {
		return s.substr(0, 9) + ".";
	}
	if (s.length() < 10) {
		while (s.length() < 10)
			s = ' ' + s;
		return s;
	}
	return s;
}

Contact* PhoneBook::getContacts() {
	return contacts;
}
