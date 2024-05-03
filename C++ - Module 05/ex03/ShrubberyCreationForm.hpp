#ifndef SHRUBBERYCRETIONFORM_HPP
#define SHRUBBERYCRETIONFORM_HPP
#include <string.h>
#include <iostream>
class AForm;
class ShrubberyCreationForm : AForm{
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

	public:
		ShrubberyCreationForm &operator=(const ShrubberyCreationForm &ncopy);
		ShrubberyCreationForm(const ShrubberyCreationForm &ncopy);
		virtual void execute(const Bureaucrat &pol) const = 0;
		ShrubberyCreationForm(std::string name2);
		~ShrubberyCreationForm();
		ShrubberyCreationForm();
};
#endif



#ifndef SHRUBBERYCRETIONFORM_HPP
#define SHRUBBERYCRETIONFORM_HPP
#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include <string.h>
#include <iostream>
class AForm;
class Bureaucrat;
class ShrubberyCreationForm : AForm{
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

	public:
		friend std::ostream &operator<<(std::ostream &stream, const ShrubberyCreationForm &f);
		virtual void execute(const Bureaucrat &pol) const = 0;
		ShrubberyCreationForm(std::string name2, int grades2, int gradee2);
		void beSigned(const Bureaucrat &pol);
		ShrubberyCreationForm &operator=(const ShrubberyCreationForm &ncopy);
		std::string getName() const;
		void check_grade(int grade);
		ShrubberyCreationForm(const ShrubberyCreationForm &ncopy);
		bool getSignedf() const;
		int getGrades() const;
		int getGradee() const;
		~ShrubberyCreationForm();
		ShrubberyCreationForm();
};
#endif