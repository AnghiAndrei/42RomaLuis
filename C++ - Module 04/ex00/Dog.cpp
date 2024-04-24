#include "Dog.hpp"
Dog::~Dog(){std::cout<<"Dog destruction"<<std::endl;}
Dog::Dog() : Animal("Dog"){std::cout<<"Dog costruction"<<std::endl;}