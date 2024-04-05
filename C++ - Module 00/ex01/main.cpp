#include "PhoneBook.hpp"

int main(){
    std::string  str;
    PhoneBook pb;
    while(1){
        std::cout<<"PhoneBook>";
        std::getline(std::cin, str);
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