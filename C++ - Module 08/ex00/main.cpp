#include "easyfind.hpp"

int main(){
	std::vector<int> lista;
	lista.push_back(69);
    lista.push_back(42);
    lista.push_back(7);
	std::cout<<easyFind(lista, 42)<<std::endl;
	std::cout<<easyFind(lista, -42)<<std::endl;
	return 0;
}
