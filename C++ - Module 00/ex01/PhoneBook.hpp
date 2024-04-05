#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP
#include "Contact.hpp"
#include <iostream>
#include <cstdlib> 
class PhoneBook{
    Contact list[10];
    int insert;

    public:
        PhoneBook();
        void add_contact();
        void search();
};
#endif