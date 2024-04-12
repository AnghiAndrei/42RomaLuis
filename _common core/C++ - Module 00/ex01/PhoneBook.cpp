/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:21:49 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/12 14:03:14 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
PhoneBook::PhoneBook(){
    insert=1;
}

void PhoneBook::add_contact()
{
	std::string temp;
    if (insert==9)
	{
        insert=1;
	}
	std::cout<<"First name: ";
    std::cin>>temp;
	list[insert].set_info("name", temp);
	std::cout<<"Last name: ";
    std::cin>>temp;
	list[insert].set_info("name2", temp);
	std::cout<<"Surname: ";
    std::cin>>temp;
	list[insert].set_info("surname", temp);
	std::cout<<"Phone: ";
    std::cin>>temp;
	list[insert].set_info("tel", temp);
	std::cout<<"Darkest secret: ";
    std::cin>>temp;
	list[insert].set_info("dse", temp);
    insert++;
}

void PhoneBook::search(){
    int i=1, i2=0;
	std::string temp;
	std::string temp2;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "|    index |firstname | lastname | surname  |" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    while(i != 9){
        std::cout<<"|        "<<i<<" |";
        i2=0;
		temp2=list[i].get_info("name");
        while (temp2[i2] != '\0' && i2 != 10)
        {
            if(i2 == 9 && temp2[i2+1] != '\0')
                std::cout<<".";
            else
                std::cout<<temp2[i2];
            i2++;
        }
        while (i2 != 10)
        {
            std::cout<<" ";
            i2++;
        }
        std::cout<<"|";
        i2=0;
		temp2=list[i].get_info("name2");
        while (temp2[i2] != '\0' && i2 != 10)
        {
            if(i2 == 9 && temp2[i2+1] != '\0')
                std::cout<<".";
            else
                std::cout<<temp2[i2];
            i2++;
        }
        while (i2 != 10)
        {
            std::cout<<" ";
            i2++;
        }
        std::cout<<"|";
        i2=0;
		temp2=list[i].get_info("surname");
        while (temp2[i2] != '\0' && i2 != 10)
        {
            if(i2 == 9 && temp2[i2+1] != '\0')
                std::cout<<".";
            else
                std::cout<<temp2[i2];
            i2++;
        }
        while (i2 != 10)
        {
            std::cout<<" ";
            i2++;
        }
        std::cout<<"|\n";
        i++;
    }
	std::cout << "---------------------------------------------" << std::endl;
    do{
        std::cout<<"SEARCH>";
        std::cin>>temp;
		i=atoi(temp.c_str());
    }while (!(i >= 1 && i < 9));
    std::cout<<"Index: "<<i<<"\nFirst name: "<<list[i].get_info("name")<<"\nLast name: "<<list[i].get_info("name2")<<"\nSurname: "<<list[i].get_info("surname")<<"\nPhone: "<<list[i].get_info("tel")<<"\nDarkest secret: "<<list[i].get_info("dse")<<std::endl;
}