#include "ScalarConverter.hpp"

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &ncopy){(void)ncopy;return *this;}
ScalarConverter::ScalarConverter(const ScalarConverter &ncopy){(*this) = ncopy;}
ScalarConverter::~ScalarConverter(){}
ScalarConverter::ScalarConverter(){}

long long int	ScalarConverter::ft_atoi(const char *string)
{
	long long int		i;
	long long int		res;
	long long int		s;

	i = 0;
	while (string[i] == ' ' || (string[i] >= 9 && string[i] <= 13))
		i++;
	s = 1;
	if (string[i] == '+' || string[i] == '-')
	{
		if (string[i] == '-')
			s = -1;
		i++;
	}
	res = 0;
	while (string[i] >= '0' && string[i] <= '9')
	{
		res = (res * 10) + (string[i] - '0');
		i++;
	}
	return (res * s);
}

float	ScalarConverter::ft_atof(const char *string)
{
	float res;
	int s=1;
	int i=0;

	while (string[i] == ' ' || (string[i] >= 9 && string[i] <= 13))
		i++;
	if (string[i] == '+' || string[i] == '-')
	{
		if (string[i] == '-')
			s = -1;
		i++;
	}
	res = 0;
	while (string[i] >= '0' && string[i] <= '9')
	{
		res = (res * 10) + (string[i] - '0');
		i++;
	}
	int i2=0;
	if(string[i]=='.')
	{
		i++;
		while (string[i] >= '0' && string[i] <= '9')
		{
			res = (res * 10) + (string[i] - '0');
			i2++;
			i++;
		}
	}
	for (int i3=0; i3!=i2; i3++)
		res=res / 10;
	return (res * s);
}

double	ScalarConverter::ft_atod(const char *string)
{
	double res;
	int s=1;
	int i=0;

	while (string[i] == ' ' || (string[i] >= 9 && string[i] <= 13))
		i++;
	if (string[i] == '+' || string[i] == '-')
	{
		if (string[i] == '-')
			s = -1;
		i++;
	}
	res = 0;
	while (string[i] >= '0' && string[i] <= '9')
	{
		res = (res * 10) + (string[i] - '0');
		i++;
	}
	int i2=0;
	if(string[i]=='.')
	{
		i++;
		while (string[i] >= '0' && string[i] <= '9')
		{
			res = (res * 10) + (string[i] - '0');
			i2++;
			i++;
		}
	}
	for (int i3=0; i3!=i2; i3++)
		res=res / 10;
	return (res * s);
}

void ScalarConverter::convert_cifd(char *str){
	if (strcmp(str, "0") == 0){
		std::cout<<"char: Non displayable\nint: 0\nfloat: 0.0f\ndouble: 0.0"<<std::endl;
		return ;
	}
	std::string special[]={"-inff", "+inff", "nanf", "-inf", "+inf", "nan"};
	for (int i2=0; i2!=6; i2++)
	{
		if (strcmp(special[i2].c_str(), str)==0){
			std::cout<<"char: impossible"<<std::endl;
			std::cout<<"int: impossible"<<std::endl;
			if (str == special[5] || str == special[2]){
				std::cout<<"float: nanf"<<std::endl;
				std::cout<<"double: nan"<<std::endl;
			}else{
				std::cout<<"float: "<<special[2]<<std::endl;
				std::cout<<"double: "<<special[2]<<std::endl;
			}
			return ;
		}
	}

	if (this->ft_atoi(str) == 0 || this->ft_atof(str)!=(int)this->ft_atof(str))
		std::cout<<"char: non displayable"<<std::endl;
	else if (this->ft_atoi(str) < 0 || this->ft_atoi(str) >= 128)
		std::cout<<"char: impossible"<<std::endl;
	else if (this->ft_atoi(str) < 32 || this->ft_atoi(str) == 127)
		std::cout<<"char: non displayable"<<std::endl;
	else
		std::cout<<"char: "<<"'" <<(char)this->ft_atoi(str)<<"'"<<std::endl;
	std::cout<<"int: "<<this->ft_atoi(str)<<std::endl;
	std::cout<<"float: "<<this->ft_atof(str);
	if(this->ft_atof(str)==(int)this->ft_atof(str))
		std::cout<<".0f";
	else
		std::cout<<"f";
	std::cout<<"\ndouble: "<<this->ft_atod(str);
	if(this->ft_atod(str)==(int)this->ft_atod(str))
		std::cout<<".0";
	std::cout<<std::endl;
}