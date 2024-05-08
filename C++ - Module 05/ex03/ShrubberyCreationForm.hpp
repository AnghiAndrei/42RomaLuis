#ifndef SHRUBBERYCRETIONFORM_HPP
#define SHRUBBERYCRETIONFORM_HPP
#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <string.h>
#include <iostream>
#include <fstream>
class Form;
class ShrubberyCreationForm : public Form{
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
		ShrubberyCreationForm &operator=(const ShrubberyCreationForm &ncopy);
		ShrubberyCreationForm(std::string name2, int grades2, int gradee2);
		ShrubberyCreationForm(const ShrubberyCreationForm &ncopy);
		virtual void execute(const Bureaucrat &pol) const;
		ShrubberyCreationForm(std::string name2);
		void beSigned(const Bureaucrat &pol);
		virtual std::string getName() const;
		~ShrubberyCreationForm();
		ShrubberyCreationForm();
		bool getSignedf() const;
		int getGrades() const;
		int getGradee() const;
};
#endif