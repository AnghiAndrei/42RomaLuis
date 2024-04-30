#include "WrongCat.hpp"
WrongCat::~WrongCat(){std::cout<<"WrongCat destruction"<<std::endl;}
WrongCat::WrongCat(const WrongCat &ncopy) : WrongAnimal(ncopy){this->type=ncopy.type;}
std::string WrongCat::getType() const{return this->type;}
WrongCat::WrongCat(){this->type="";}
WrongCat::WrongCat(std::string type2){
    std::cout<<"WrongCat costructor"<<std::endl;
    this->type=type2;
}

WrongCat &WrongCat::operator=(WrongCat &ncopy){
    this->type=ncopy.type;
    return *this;
}
