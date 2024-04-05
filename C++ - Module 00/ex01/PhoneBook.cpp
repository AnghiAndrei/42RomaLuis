#include "PhoneBook.hpp"
PhoneBook::PhoneBook(){
    insert=0;
}

void PhoneBook::add_contact()
{
    if (insert==9)
	{
        insert=0;
	}
	std::cout<<"First name: ";
    std::cin>>list[insert].name;
    std::cout<<"Last name: ";
    std::cin>>list[insert].name2;
    std::cout<<"Surname: ";
    std::cin>>list[insert].surname;
    std::cout<<"Phone: ";
    std::cin>>list[insert].tel;
    std::cout<<"Darkest secret: ";
    std::cin>>list[insert].dse;
    insert++;
}

void PhoneBook::search(){
    int i=0, i2=0;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "|    index |firstname | lastname | surname  |" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    while(i != 9){
        std::cout<<"|        "<<i<<" |";
        i2=0;
        while (list[i].name[i2] != '\0' && i2 != 9)
        {
            if(i2 == 9 && list[i].name[i2+1] != '\0')
                std::cout<<".";
            else
                std::cout<<list[i].name[i2];
            i2++;
        }
        while (i2 != 10)
        {
            std::cout<<" ";
            i2++;
        }
        std::cout<<"|";
        i2=0;
        while (list[i].name2[i2] != '\0' && i2 != 9)
        {
            if(i2 == 9 && list[i].name2[i2+1] != '\0')
                std::cout<<".";
            else
                std::cout<<list[i].name2[i2];
            i2++;
        }
        while (i2 != 10)
        {
            std::cout<<" ";
            i2++;
        }
        std::cout<<"|";
        i2=0;
        while (list[i].surname[i2] != '\0' && i2 != 9)
        {
            if(i2 == 9 && list[i].surname[i2+1] != '\0')
                std::cout<<".";
            else
                std::cout<<list[i].surname[i2];
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
        std::cin>>i;
    }while (!(i > -1 && i < 8));
    std::cout<<"Index: "<<i<<"\nFirst name: "<<list[i].name<<"\nLast name: "<<list[i].name2<<"\nSurname: "<<list[i].surname<<"\nPhone: "<<list[i].tel<<"\nDarkest secret: "<<list[i].dse<<std::endl;;
}