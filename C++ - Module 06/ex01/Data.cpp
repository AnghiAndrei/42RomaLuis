#include "Data.hpp"

Data &Data::operator=(const Data &ncopy){(void)ncopy;return *this;}
Data::Data(const Data &ncopy){(*this) = ncopy;}
Data::~Data(){}
Data::Data(){}