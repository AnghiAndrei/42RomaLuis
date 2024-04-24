#include "Animal.hpp"
Animal::~Animal(){std::cout<<"Animal destruction"<<std::endl;}
std::string Animal::get_Type(){return this->type;}
Animal::Animal(std::string type2){
    std::cout<<"Animal costructor"<<std::endl;
    this->type=type2;
}
Animal &operator=(Animal &copy){
    this->type=copy->get_Type();
    return *this;
}