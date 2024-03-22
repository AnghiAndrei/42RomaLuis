#include "Bureaucrat.hpp"

int main()
{
	try
	{
		Bureaucrat bureaucrat("John", 5);
		bureaucrat.upGrade(2);
		bureaucrat.downGrade(1);
		bureaucrat.downGrade(7);
		//bureaucrat.upGrade(13); //eccezione
		//Bureaucrat bureaucrat2("Alessio", 152);
		//Bureaucrat bureaucrat3("Alessio", -2);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	return 0;
}
