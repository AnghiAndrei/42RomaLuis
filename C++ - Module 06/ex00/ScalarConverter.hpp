#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP
#include "iostream"
#include "string.h"
class ScalarConverter{
    ScalarConverter();
    public:
        ScalarConverter &operator=(const ScalarConverter &ncopy);
		static long long int ft_atoi(const char *string);
        ScalarConverter(const ScalarConverter &ncopy);
		static double ft_atod(const char *string);
		static float ft_atof(const char *string);
        static void convert_cifd(char *str);
        ~ScalarConverter();
};
#endif