#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP
#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
class Form;
class PresidentialPardonForm : public Form{
	const int grades;
	const int gradee;
	const std::string name;
	bool signedf;

	class GradeTooHighException : public std::exception{
		public:
			const char *what() const throw(){return "Grade too high\n";}
	};

	class GradeTooLowException : public std::exception{
		public:
			const char *what() const throw(){return "Grade too low\n";}
	};

	class FormNotFirmedException : public std::exception{
		public:
			const char *what() const throw(){return "Form not firmed\n";}
	};

	class FileOpenException : public std::exception{
		public:
			const char *what() const throw(){return "File error\n";}
	};

	public:
		PresidentialPardonForm &operator=(const PresidentialPardonForm &ncopy);
		PresidentialPardonForm(std::string name2, int grades2, int gradee2);
		PresidentialPardonForm(const PresidentialPardonForm &ncopy);
		virtual void execute(const Bureaucrat &pol) const;
		PresidentialPardonForm(std::string name2);
		void beSigned(const Bureaucrat &pol);
		std::string getName() const;
		~PresidentialPardonForm();
		PresidentialPardonForm();
		bool getSignedf() const;
		int getGrades() const;
		int getGradee() const;
};
#endif