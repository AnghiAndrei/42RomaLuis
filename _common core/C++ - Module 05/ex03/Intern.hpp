#ifndef INTERN_HPP
#define INTERN_HPP
#include "Form.hpp"
#include "PresidentialPardonForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
class Intern{
	class NoFormValid : public std::exception{
		public:
			const char *what() const throw(){return "Form not valid\n";}
	};

	public:
		Form *makeForm(std::string name, std::string targhet);
		Intern &operator=(const Intern &ncopy);
		Intern(const Intern &ncopy);
		~Intern();
		Intern();
};
#endif