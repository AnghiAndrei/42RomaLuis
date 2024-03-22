#include "Intern.hpp"

int Intern::checkForm(std::string form)
{
	std::string name[4] = {"presidential", "robotomy", "shrubbery"};
	int i;
	for (i = 0; i < 3; i++)
	{
		if (!name[i].find(form))
			break;
	}
	return i;
}

Intern::Intern()
{
	std::cout << "Intern created with default constructor" << std::endl;
}

Intern::~Intern()
{
	std::cout << "Intern destroyed" << std::endl;
}

Intern::Intern(const Intern &toCopy)
{
	*this = toCopy;
	std::cout << "Intern created with copy constructor" << std::endl;
}

Intern &Intern::operator=(const Intern &toCopy)
{
	if (this != &toCopy)
	{
		*this = toCopy;
	}
	return *this;
}

AForm *Intern::makeForm(std::string form, std::string target)
{
	AForm *f;
	int i = checkForm(form);
	switch (i)
	{
	case 0:
		f = new PresidentialPardonForm(target);
		break;
	case 1:
		f = new RobotomyRequestForm(target);
		break;
	case 2:
		f = new ShrubberyCreationForm(target);
		break;
	default:
		throw FormNotException();
		return NULL;
		break;
	}
	std::cout << "Intern creates " << *f << std::endl;
	return f;
}
