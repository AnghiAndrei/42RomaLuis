#include "Span.hpp"

Span::Span(const Span &ncopy){*this=ncopy;}
Span::Span(unsigned int nbr){this->size=nbr;}
Span::Span(){this->size=0;}
Span::~Span(){}

void Span::addNumber(int nbr){
	if (span.size() < this->size)
		span.push_back(nbr);
	else
		throw std::out_of_range("segmentation fault (core dumped)");
};

Span &Span::operator=(const Span &ncopy){
    *this=ncopy;
    return *this;
}

int Span::shortestSpan(){
    if (span.size() < 2)
        throw std::runtime_error("Non ci sono abbastanza elementi per calcolare lo span.");
    std::deque<int> sortedSpan(span);
    std::sort(sortedSpan.begin(), sortedSpan.end());
    int minSpan = std::numeric_limits<int>::max();
    for (size_t i = 1; i < sortedSpan.size(); ++i){
        int span=sortedSpan[i]-sortedSpan[i-1];
        if (span < minSpan)
            minSpan=span;
    }
    return minSpan;
}

int Span::longestSpan(){
    if (span.size() < 2)
        throw std::runtime_error("Non ci sono abbastanza elementi per calcolare lo span.");
    int minElement = *std::min_element(span.begin(), span.end());
    int maxElement = *std::max_element(span.begin(), span.end());
    return maxElement - minElement;
}