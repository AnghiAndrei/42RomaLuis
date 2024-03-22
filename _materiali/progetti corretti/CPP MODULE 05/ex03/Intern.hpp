#ifndef INTERN_HPP
#define INTERN_HPP

#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern
{
private:
	int checkForm(std::string form);

public:
	Intern(/* args */);
	~Intern();
	Intern(const Intern &toCopy);
	Intern &operator=(const Intern &toCopy);
	AForm *makeForm(std::string form, std::string target);
	class FormNotException : public std::exception
	{
	public:
		const char *what() const throw()
		{
			return "Non esiste il form inserito\n";
		}
	};
};
#endif
