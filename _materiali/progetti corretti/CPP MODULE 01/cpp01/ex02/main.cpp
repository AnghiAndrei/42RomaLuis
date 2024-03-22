#include <string>
#include <iostream>

int main()
{
    std::string str = "HI THIS IS MY BRAIN";
    std::string* stringPTR = &str;
    /*when i init a ref to an existing variabe in this case create
    another copy of the var it becomes an alias to the same memory location
    Unlike the pointer  a ref must be init once is init it cannot be made to
    refer to a differnt object it always refere to the same object*/
    std::string& stringREF = str; //init a ref to a string

    std::cout << "string address: " << stringPTR << std::endl;
    std::cout << "stringPTR address: " << stringPTR << std::endl;
    std::cout << "stringREF string: " << &stringREF << std::endl;
    std::cout << "stringPTR string: " << *stringPTR << std::endl;
    std::cout << "stringREF string: " << stringREF << std::endl;

}
