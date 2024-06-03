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
	try{
		sp3.addNumber(7);
	}catch(const std::exception& e){std::cout<<e.what()<<std::endl;}

	std::vector<int> vec;
	int N=2000;
    for (int i = 1; i != N; i++)vec.push_back(i);
	try{
		Span sp5(100);
		sp5.addNumbers(vec);
	}catch(const std::exception& e){std::cout<<e.what()<<std::endl;}
	try{
		Span sp6(N);
		sp6.addNumber(7);
		sp6.addNumbers(vec);
	}catch(const std::exception& e){std::cout<<e.what()<<std::endl;}
	Span sp4(N);
	sp4.addNumbers(vec);
	std::cout<<sp4.shortestSpan()<<std::endl;
	std::cout<<sp4.longestSpan()<<std::endl;
	return 0;
}