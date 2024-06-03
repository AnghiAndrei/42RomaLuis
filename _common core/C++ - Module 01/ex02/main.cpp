#include <string>
#include <iostream>
int main(){
    std::string str="HI THIS IS BRAIN";
    std::string *stringPTR=&str;
    std::string& stringREF=str;
    std::cout<<"String address: "<<stringPTR<<std::endl;
    std::cout<<"StringPTR address: "<<stringPTR<<std::endl;
    std::cout<<"StringREF address: "<<&stringREF<<std::endl;
    std::cout<<"StringPTR string: "<<*stringPTR<<std::endl;
    std::cout<<"StringREF string: "<<stringREF<<std::endl;
    std::cout<<"String string: "<<str<<std::endl;
    return 0;
}