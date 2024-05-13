/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:08:47 by lnicoter          #+#    #+#             */
/*   Updated: 2024/05/02 15:48:07 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <cstdlib> // Per la funzione rand() e srand()
#include <ctime>
/*
possibile che debbano esserci
più funzioni per i costruttori?
array di oggetti template
metodo size() per avere la grandezza
dell'array sempre a portata di mano, questo penso serva
*/
template <typename T>

class Array
{
	private:
		unsigned int	sizeA;
		T				*elementArr;
	public:
		Array();
		Array(unsigned int n);
		~Array();
		Array(Array& obj);
		Array& operator=(const Array& obj);
		unsigned int	size();
		T&	operator[](size_t idx);
};

template <typename T>
Array<T>::Array()
{
	std::cout<<"Basic array constructor called"<<std::endl;
	elementArr = new T[0];
	sizeA = 0;
}

template <typename T>
Array<T>::Array(unsigned int n)
{
	std::cout<<"Defined array constructor called"<<std::endl;
	this->elementArr = new T[n];
	this->sizeA = n;
}

template <typename T>
Array<T>::~Array()
{
	std::cout<<"Array destructor called"<<std::endl;
	delete [] elementArr;
}
template <typename T>
unsigned int Array<T>::size()
{
	//is it possible to do this with the out of bounds?
	return this->sizeA;
}

template <typename T>
Array<T>::Array(Array& obj)
{
	if (this == &obj)
		return ;
	this->sizeA = obj.size();
	this->elementArr = new T[this->sizeA];
	for (unsigned int i = 0; i < this->sizeA; i++)
	{
		this->elementArr[i] = obj.elementArr[i];
	}
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& obj)
{
	if (this == &obj)
		return *this;
	this->sizeA = obj.size();
	this->elementArr = new T[this->sizeA];
	for (int i = 0; i < this->sizeA; i++)
	{
		this->elementArr[i] = obj.elementArr[i];
	}
	return *this;
}

/*
i do the overloading of the [] operator
in order to print the values in the main without using
precise functions to print exactly the elements of
elementArr
*/
template <typename T>
T& Array<T>::operator[](size_t idx)
{
	if (idx >= this->sizeA)
		throw std::out_of_range("index out of bounds");
	return this->elementArr[idx];
}


//it seems that trying to use a tpp file is a no go
#endif
