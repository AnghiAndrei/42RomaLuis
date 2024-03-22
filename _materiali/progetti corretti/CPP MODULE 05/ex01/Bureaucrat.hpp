#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include <iostream>
#include <string>
#include <exception>
#include "Form.hpp"

class Form;

class Bureaucrat
{
private:
	const std::string name;
	int grade; // 1 highest possible grade - 150 lowest

	class GradeTooHighException : public std::exception
	{
	public:
		const char *what() const throw()
		{
			return "Il valore è troppo alto\n";
		}
	};

	class GradeTooLowException : public std::exception
	{
	public:
		const char *what() const throw()
		{
			return "Il valore è troppo basso\n";
		}
	};

public:
	Bureaucrat(std::string name, int grade);
	Bureaucrat(const Bureaucrat &toCopy);
	Bureaucrat &operator=(const Bureaucrat &toCopy);
	~Bureaucrat();
	std::string getName() const;
	int getGrade() const;
	void upGrade(int amount);
	void downGrade(int amount);
	void signForm(Form &form);
};
std::ostream&	operator<<(std::ostream& os, const Bureaucrat& bureaucrat);

#endif
