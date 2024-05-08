#include "Serializer.hpp"

Serializer &Serializer::operator=(const Serializer &ncopy){(void)ncopy;return *this;}
Serializer::Serializer(const Serializer &ncopy){(*this) = ncopy;}
Serializer::~Serializer(){}
Serializer::Serializer(){}