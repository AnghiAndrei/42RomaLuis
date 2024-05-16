#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP
#include <iostream>
#include <string.h>
#include <stdint.h>

typedef struct Data{
	std::string str;
}Data;

class Serializer{
	Serializer();
	public:
		Serializer &operator=(const Serializer &ncopy);
		static Data* deserialize(uintptr_t raw);
		static uintptr_t serialize(Data* ptr);
		Serializer(const Serializer &ncopy);
		~Serializer();
};
#endif