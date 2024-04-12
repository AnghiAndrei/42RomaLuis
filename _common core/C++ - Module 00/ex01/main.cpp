/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:21:44 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/12 14:01:59 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

int main(){
    std::string  str;
    PhoneBook pb;
    while(1){
        std::cout<<"PhoneBook>"<<std::endl;
		std::cin>>str;
        if (str=="EXIT")
            return 0;
        else if (str=="SEARCH")
            pb.search();
        else if (str=="ADD")
            pb.add_contact();
        else
            std::cout<<"WTF?"<<std::endl;
    }
    return 0;
}