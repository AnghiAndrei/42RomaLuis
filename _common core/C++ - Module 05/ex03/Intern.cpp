#include "Intern.hpp"

Intern::Intern(const Intern &ncopy){(void)ncopy;}
Intern::~Intern(){}
Intern::Intern(){}

Intern &Intern::operator=(const Intern &ncopy){
	(void)ncopy;
	return *this;
}

Form *Intern::makeForm(std::string name, std::string targhet){
	Form *nf;
	std::string arrayf[4] = {"presidential", "robotomy request", "shrubbery"};
	int i;
	for (i = 0; i < 3; i++)
	{
		if (!arrayf[i].find(name))
			break;
	}
	switch (i)
	{
		case 0:
			nf=new ShrubberyCreationForm(targhet);
			break;
		case 1:
			nf=new RobotomyRequestForm(targhet);
			break;
		case 2:
			nf=new PresidentialPardonForm(targhet);
			break;
		default:
			throw NoFormValid();
			break;
	}
	std::cout<<"Intern creates "<<targhet<<std::endl;
	return nf;
}