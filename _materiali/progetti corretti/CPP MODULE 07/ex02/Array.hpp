/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:32:56 by lde-mich          #+#    #+#             */
/*   Updated: 2024/03/04 12:53:17 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

template <typename T>
class Array
{
	private:
		T *arr;
		unsigned int sizeArr;

	public:
	
		unsigned int size();

		Array &operator=(Array const &obj);
		T &operator[](unsigned int i);

		Array(unsigned int n);
		Array(Array const &obj);
		Array();
		~Array();


		class OutOfBoundsException: public std::exception
        {
            public:
                virtual const char	*what() const throw()
				{
					return ("Error, index out of bounds");
				};
        };

};

template <typename T>
Array<T>::Array()
{
	this->arr = new T[0];
	this->sizeArr = 0;
}

template <typename T>
Array<T>::Array(Array const &obj)
{
	this->arr = 0;
	this->sizeArr = 0;
	(*this) = obj;
}

template <typename T>
Array<T>::Array(unsigned int n)
{
	this->sizeArr = n;
	this->arr = new T[n];

	for (unsigned int i = 0; i < n; i++)
		this->arr[i] = 0;
}

template <typename T>
Array<T>::~Array()
{
	delete [] this->arr;
	this->arr = NULL;
}

template <typename T>
unsigned int Array<T>::size()
{
	return (this->sizeArr);
}

template <typename T>
T &Array<T>::operator[](unsigned int i)
{
	if(i >= this->sizeArr)
		throw Array<T>::OutOfBoundsException();
	return (this->arr[i]);
}

template <typename T>
Array<T> &Array<T>::operator=(Array const &obj)
{
	if (this == &obj)
		return (*this);
	
	this->sizeArr = obj.sizeArr;
	
	delete [] this->arr;
	
	if (this->sizeArr)
	{
		this->arr = new T[obj.sizeArr];

		for (unsigned int i = 0; i < this->sizeArr; i++)
			this->arr[i] = obj.arr[i];
	}
	else
		this->arr = 0;

	return (*this);
}









