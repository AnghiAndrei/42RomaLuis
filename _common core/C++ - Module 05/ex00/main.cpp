#include "Bureaucrat.hpp"

int main(){
	try
	{
		Bureaucrat Mussolini("Mussolini", 5);
		Mussolini.upGrade(2);
		Mussolini.downGrade(1);
		Mussolini.downGrade(7);
		std::cout<<Mussolini;
		// Mussolini.upGrade(152);
		// Mussolini.upGrade(-152);
		// Bureaucrat Mussolini2("Renzi", 152);
		// Bureaucrat Mussolini3("Giorgia Meloni", -2);
	}
	catch (const std::exception &e){
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	return 0;
}