/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:25:13 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/12 13:49:30 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

std::string Contact::get_info(std::string str){
	if(str=="name")
		return this->name;
	else if(str=="name2")
		return this->name2;
	else if(str=="surname")
		return this->surname;
	else if(str=="dse")
		return this->dse;
	else if(str=="tel")
		return this->tel;
	return NULL;
}

void Contact::set_info(std::string str, std::string str2){
	if(str=="name")
		this->name=str2;
	else if(str=="name2")
		this->name2=str2;
	else if(str=="surname")
		this->surname=str2;
	else if(str=="dse")
		this->dse=str2;
	else if(str=="tel")
		this->tel=str2;
}