#include "Bureaucrat.hpp"

int main(){
	try
	{
		Bureaucrat berluscuni("Berluscuni", 5);
		berluscuni.upGrade(2);
		berluscuni.downGrade(1);
		berluscuni.downGrade(7);
		std::cout<<berluscuni;
		// berluscuni.upGrade(152);
		// berluscuni.upGrade(-152);
		// Bureaucrat berluscuni2("Renzi", 152);
		// Bureaucrat berluscuni3("Giorgia Meloni", -2);
	}
	catch (const std::exception &e){
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	return 0;
}