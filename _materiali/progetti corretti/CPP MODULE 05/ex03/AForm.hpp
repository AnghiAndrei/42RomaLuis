#ifndef FORM_HPP
# define FORM_HPP
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm
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

	class NotSignedException : public std::exception
	{
	public:
		const char *what() const throw()
		{
			return "Il form non è firmato\n";
		}
	};

public:
	AForm(std::string name, int const gradeSign, int const gradeExecute);
	AForm(const AForm &toCopy);
	virtual AForm &operator=(const AForm &toCopy);
	virtual ~AForm();
	bool beSigned(Bureaucrat const &bure);
	bool getSigned() const;
	int getGradeSign() const;
	int getGradeExecute() const;
	std::string getName() const;
	virtual void execute(Bureaucrat const & executor) const = 0;
	void setSigned(bool value);
	void checkExecute(Bureaucrat const & executor) const;
};

std::ostream&	operator<<(std::ostream& os, const AForm& form);
#endif



