#include "Serializer.hpp"

int main(){
	Data *ptr = new Data;
	Data *new_ptr;
	uintptr_t	raw;

	ptr->str = "Voglio mangiare il tuo pancreas!";

	raw = Serializer::serialize(ptr);
	new_ptr = Serializer::deserialize(raw);

	std::cout << "ptr--> " << ptr << std::endl;
	std::cout << "new_ptr--> " << new_ptr << std::endl;

	return 0;
}