#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP
#include "Contact.hpp"
#include <iostream>
class PhoneBook{
    Contact list[9];
    int insert;

    public:
        PhoneBook();
        void add_contact();
        void search();
};
#endif