#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP
#include "iostream"
#include "string.h"
class ScalarConverter{
    public:
        ScalarConverter &operator=(const ScalarConverter &ncopy);
        ScalarConverter(const ScalarConverter &ncopy);
		long long int ft_atoi(const char *string);
		double ft_atod(const char *string);
		float ft_atof(const char *string);
        void convert_cifd(char *str);
        ~ScalarConverter();
        ScalarConverter();
};
#endif