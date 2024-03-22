#ifndef FORM_HPP
# define FORM_HPP
#include <string>
#include <iostream>
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
private:
	std::string const _name;
	bool _signed;
	int const _gradeSign;
	int const _gradeExecute;

	class GradeTooHighException : public std::exception
	{
	public:
		const char *what() const throw()
		{
			return "Il grado è troppo alto per il form\n";
		}
	};

	class GradeTooLowException : public std::exception
	{
	public:
		const char *what() const throw()
		{
			return "Il grado è troppo basso per il form\n";
		}
	};
public:
	Form(std::string name, int const gradeSign, int const gradeExecute);
	Form(const Form &toCopy);
	Form &operator=(const Form &toCopy);
	~Form();
	bool beSigned(Bureaucrat const &bure);
	bool getSigned() const;
	int getGradeSign() const;
	int getGradeExecute() const;
	std::string getName() const;
};

std::ostream&	operator<<(std::ostream& os, const Form& form);
#endif



