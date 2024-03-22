#include <iostream>
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
	// Creazione di un bureaucrat e di alcuni form
	Bureaucrat bureaucrat("John", 1);
	Bureaucrat bureaucrat2("Anna",150);
	ShrubberyCreationForm shrubberyForm("home");
	RobotomyRequestForm robotomyForm("Evaluator");
	PresidentialPardonForm pardonForm("Evaluator");

	// Test di firma e esecuzione dei form
	try
	{
		bureaucrat2.signForm(shrubberyForm);
		bureaucrat.signForm(shrubberyForm);
		bureaucrat.signForm(robotomyForm);
		bureaucrat2.signForm(robotomyForm);
		bureaucrat.signForm(pardonForm);
		bureaucrat.executeForm(shrubberyForm);
		bureaucrat.executeForm(robotomyForm);
		bureaucrat.executeForm(pardonForm);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	return 0;
}
