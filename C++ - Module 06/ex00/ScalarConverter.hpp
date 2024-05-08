#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP
class ScalarConverter{
    public:
        ScalarConverter &operator=(const &ncopy);
        ScalarConverter(const &ncopy);
        void convert_cifd(char *str);
        ~ScalarConverter();
        ScalarConverter();
};
#endif