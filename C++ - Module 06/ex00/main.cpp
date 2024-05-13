#include "ScalarConverter.hpp"

int main(int argc, char **argv){
	if (argc!=2){
		std::cout<<"Marshal: Input error"<<std::endl;
		return -1;
	}
	ScalarConverter::convert_cifd(argv[1]);
	return 0;
}