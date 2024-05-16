#ifndef ARRAY_HPP
#define ARRAY_HPP
#include <string.h>
#include <iostream>

template<typename T>
class Array{
	unsigned int Size;
    T *array;
    public:
        unsigned int size() const{return Size;}
        ~Array(){delete [] this->array;}
        Array(){}

        Array &operator=(const Array &ncopy){
			if (this == &ncopy)
				return (*this);
			this->Size=ncopy.size();
			this->array = new T[ncopy.size()];
			for(unsigned int i=0;i!=this->Size;i++)
				this->array[i]=ncopy.array[i];
            return *this;
        }
        T& operator[](unsigned int index) {
            if (index>=this->Size)
                throw std::out_of_range("segmentation fault (core dumped)");
            return array[index];
        }
        Array(const Array &ncopy){
			this->array = 0;
			this->Size = 0;
			(*this) = ncopy;
        }
		Array(unsigned int size2){
			this->Size=size2;
			this->array = new T[this->Size];
            for(unsigned int i=0;i!=size2;i++)
                this->array[i]=T();
        }
};
#endif