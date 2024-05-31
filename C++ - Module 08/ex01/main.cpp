#include"Span.hpp"
int main()
	{
	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	try{
		sp.addNumber(7);
	}catch(const std::exception& e){std::cout<<e.what()<<std::endl;}
	std::cout<<sp.shortestSpan()<<std::endl;
	std::cout<<sp.longestSpan()<<std::endl;

	Span sp2 = Span(5);
	sp2.addNumber(6);
	try{
		std::cout<<sp2.longestSpan()<<std::endl;
	}catch(const std::exception& e){std::cout<<e.what()<<std::endl;}
	try{
		std::cout<<sp2.shortestSpan()<<std::endl;
	}catch(const std::exception& e){std::cout<<e.what()<<std::endl;}
	Span sp3;
	return 0;
}