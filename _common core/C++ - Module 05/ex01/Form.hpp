#ifndef FORM_HPP
#define FORM_HPP
#include "Bureaucrat.hpp"
#include <string.h>
#include <iostream>
class Bureaucrat;
class Form{
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
		Form(std::string name2, int grades2, int gradee2);
		void beSigned(const Bureaucrat &pol);
		Form &operator=(const Form &ncopy);
		std::string getName() const;
		void check_grade(int grade);
		Form(const Form &ncopy);
		bool getSignedf() const;
		int getGrades() const;
		int getGradee() const;
		~Form();
		Form();
};
std::ostream &operator<<(std::ostream &stream, const Form &f);
#endif