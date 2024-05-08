#ifndef SERIALIZATION_HPP
#define SERIALIZATION_HPP
#include "iostream"
#include "string.h"
class Serialization{
    Serialization &operator=(const Serialization &ncopy);
	Serialization(const Serialization &ncopy);
	static uintptr_t serialize(Data* ptr);
	static Data* deserialize(uintptr_t raw);
    ~Serialization();
    Serialization();
};
#endif