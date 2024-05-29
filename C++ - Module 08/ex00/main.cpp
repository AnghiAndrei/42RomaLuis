#include "easyfind.hpp"

int main(){
	std::cout<<easyFind("hola", 'a')<<std::endl;
	std::cout<<easyFind((char *)"hola", 'a')<<std::endl;
	std::cout<<easyFind((const char *)"hola", 'a')<<std::endl;
	std::cout<<easyFind((std::string)"hola", 'a')<<std::endl;
	std::cout<<easyFind((const std::string)"hola", 'a')<<std::endl;
	std::cout<<easyFind((const std::string)"hola", 'a')<<std::endl;

	std::cout<<easyFind("hola", '!')<<std::endl;
	std::cout<<easyFind((char *)"hola", '!')<<std::endl;
	std::cout<<easyFind((const char *)"hola", '!')<<std::endl;
	std::cout<<easyFind((std::string)"hola", '!')<<std::endl;
	std::cout<<easyFind((const std::string)"hola", '!')<<std::endl;
	std::cout<<easyFind((const std::string)"hola", '!')<<std::endl;
	return 0;
}
