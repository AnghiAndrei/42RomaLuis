#include "easyfind.hpp"
#include <string.h>

int main(){
	easyfind("hola", 'a');
	easyfind((char *)"hola", 'a');
	easyfind((const char *)"hola", 'a');
	easyfind((std::string)"hola", 'a');
	easyfind((const std::string)"hola", 'a');
	return 0;
}
