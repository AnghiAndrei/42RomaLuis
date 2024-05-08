#include "ScalarConverter.hpp"

ScalarConverter &operator=(const &ncopy){(void)ncopy;return *this;}
ScalarConverter(const &ncopy){(*this) = ncopy;}
~ScalarConverter(){}
ScalarConverter(){}

void convert_cifd(char *str){
    std::cout<<"char: "<<(char)*str<<"\nint: "<<(int)*str<<"\nfloat: "<<(float)*str<<"\ndouble: "<<(double)*str<<std::endl;
}