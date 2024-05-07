#include "PresidentialPardonForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "Form.hpp"

int main(){
	try
	{
		Bureaucrat Mussolini("Mussolini", 1);
		Intern someRandomIntern;
		Form* rrf=someRandomIntern.makeForm("robotomy request", "Bender");
		if(rrf){}
	}
	catch (const std::exception &e){
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	return 0;
}