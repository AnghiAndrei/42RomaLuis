#ifndef SPAN_HPP
#define SPAN_HPP
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <limits>
#include <vector>
#include <deque>
class Span{
	std::deque<int> span;
    unsigned int size;
    public:
		void addNumbers(std::vector<int> vec);
        Span &operator=(const Span &ncopy);
        Span(const Span &ncopy);
		void addNumber(int nbr);
        Span(unsigned int nbr);
		int shortestSpan();
		int longestSpan();
        ~Span();
        Span();
};
#endif