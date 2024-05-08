#ifndef SERIALIZATION_HPP
#define SERIALIZATION_HPP
#include "iostream"
#include "string.h"
class Serialization{
    Serialization &operator=(const Serialization &ncopy);
	Serialization(const Serialization &ncopy);
    ~Serialization();
    Serialization();
} static;
#endif