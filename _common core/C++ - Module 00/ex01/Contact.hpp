/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:21:37 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/12 13:48:51 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP
#include <string>
#include <iostream>
class Contact{
    std::string name;
    std::string name2;
    std::string surname;
    std::string dse;
    std::string tel;

	public:
		void set_info(std::string str, std::string str2);
		std::string get_info(std::string str);
};
#endif