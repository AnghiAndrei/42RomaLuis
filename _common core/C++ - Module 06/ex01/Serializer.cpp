#include "Serializer.hpp"

Serializer &Serializer::operator=(const Serializer &ncopy){(void)ncopy;return *this;}
uintptr_t Serializer::serialize(Data* ptr){return reinterpret_cast<uintptr_t>(ptr);}
Data* Serializer::deserialize(uintptr_t raw){return reinterpret_cast<Data *>(raw);}
Serializer::Serializer(const Serializer &ncopy){(*this) = ncopy;}
Serializer::~Serializer(){}
Serializer::Serializer(){}
