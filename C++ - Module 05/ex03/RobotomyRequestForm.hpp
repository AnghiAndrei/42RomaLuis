#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP
#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
class Form;
class RobotomyRequestForm : public Form{
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
		RobotomyRequestForm &operator=(const RobotomyRequestForm &ncopy);
		RobotomyRequestForm(std::string name2, int grades2, int gradee2);
		RobotomyRequestForm(const RobotomyRequestForm &ncopy);
		virtual void execute(const Bureaucrat &pol) const;
		RobotomyRequestForm(std::string name2);
		void beSigned(const Bureaucrat &pol);
		virtual std::string getName() const;
		~RobotomyRequestForm();
		RobotomyRequestForm();
		bool getSignedf() const;
		int getGrades() const;
		int getGradee() const;
};
#endif