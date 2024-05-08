#ifndef ARRAY_HPP
#define ARRAY_HPP
#include <string.h>
#include <iostream>

template<typename T, size_t Size>
class Array{
    T array[Size];
    public:
        size_t size() const{return Size;}
        ~Array(){}

        Array &operator=(const Array &ncopy){
            for(size_t i=0;i!=Size;i++)
                this->array[i]=ncopy->array[i];
            return *this;
        }
        T& operator[](size_t index) {
            if (index >= Size)
                throw std::out_of_range("Index out of range");
            return array[index];
        }
        Array(const Array &ncopy){
            for(size_t i=0;i!=Size;i++)
                this->array[i]=ncopy->array[i];
        }
        Array(){
            for(size_t i=0;i!=Size;i++)
                this->array[i]=T();
        }
};
#endif