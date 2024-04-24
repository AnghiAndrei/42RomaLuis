#include "Cat.hpp"
Cat::~Cat(){std::cout<<"Cat destruction"<<std::endl;}
Cat::Cat() : Animal("Cat"){std::cout<<"Cat costruction"<<std::endl;}