/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:23:18 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/01/21 16:53:37 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

void Contact::createContact() {

	std::string input;
	clearerr(stdin);
	std::cin.clear();

	std::cout << "Insert First Name: ";
	std::getline(std::cin, input);
	this->setFirstName(input);

	std::cout << "Insert Last Name: ";
	std::getline(std::cin, input);
	this->setLastName(input);

	std::cout << "Insert Nick Name: ";
	std::getline(std::cin, input);
	this->setNickName(input);

	std::cout << "Insert Phone Number: ";
	std::getline(std::cin, input);
	this->setPhoneNumber(input);

	std::cout << "Insert Darkest Secret: ";
	std::getline(std::cin, input);
	this->setDarkestSecret(input);

	if (firstName.empty() || lastName.empty() || nickName.empty() || phoneNumber.empty() || darkestSecret.empty()) {
		std::cout << "\nError: empty field.\n\n";
		createContact();
	}
	return ;
}

Contact::Contact() {}

Contact::Contact(const std::string first, const std::string last, const std::string nick, const std::string phone, const std::string secret)
	: firstName(first), lastName(last), nickName(nick), phoneNumber(phone), darkestSecret(secret) {}

std::string Contact::getFirstName() const {
	return firstName;
}

std::string Contact::getLastName() const {
	return lastName;
}

std::string Contact::getNickName() const {
	return nickName;
}

std::string Contact::getPhoneNumber() const {
	return phoneNumber;
}

std::string Contact::getDarkestSecret() const {
	return darkestSecret;
}

void Contact::setFirstName(const std::string first) {
	firstName = first;
}

void Contact::setLastName(const std::string last) {
	lastName = last;
}

void Contact::setNickName(const std::string nick) {
	nickName = nick;
}

void Contact::setPhoneNumber(const std::string phone) {
	phoneNumber = phone;
}

void Contact::setDarkestSecret(const std::string secret) {
	darkestSecret = secret;
}

std::string Contact::toString() const {
	return "First Name: " + firstName +
		   "\nLast Name: " + lastName +
		   "\nNick Name: " + nickName +
		   "\nPhone Number: " + phoneNumber +
		   "\nDarkest Secret: " + darkestSecret;
}
