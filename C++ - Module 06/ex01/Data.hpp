#ifndef DATA_HPP
#define DATA_HPP
#include "iostream"
#include "string.h"
class Data{
    Data &operator=(const Data &ncopy);
	Data(const Data &ncopy);
	static uintptr_t serialize(Data* ptr);
	static Data* deserialize(uintptr_t raw);
    ~Data();
    Data();
};
#endif