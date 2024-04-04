#include "PhoneBook.hpp"
#include "Contract.hpp"
#include <iostream>
#include <string>

int main(){
    std::string  str;
    PhoneBook pb;
    while(1){
        std::cout<<"PhoneBook>";
        std::cin>>str;
        if (str=="EXIT")
            exit(0);
        else if (str=="SEARCH")
            pb.search();
        else if (str=="ADD"){
            Contact new_c;
            pb.add(new_c);
        }else
            std::cout<<"WTF?\n";
    }
    return 0;
}