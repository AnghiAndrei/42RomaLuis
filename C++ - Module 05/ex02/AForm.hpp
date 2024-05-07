#ifndef AFORM_HPP
#define AFORM_HPP
#include "Bureaucrat.hpp"
#include <string.h>
#include <iostream>
class Bureaucrat;
class AForm{
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
		friend std::ostream &operator<<(std::ostream &stream, const AForm &f);
		virtual void execute(const Bureaucrat &pol) const = 0;
		AForm(std::string name2, int grades2, int gradee2);
		void beSigned(const Bureaucrat &pol);
		AForm &operator=(const AForm &ncopy);
		std::string getName() const;
		void check_grade(int grade);
		AForm(const AForm &ncopy);
		bool getSignedf() const;
		int getGrades() const;
		int getGradee() const;
		~AForm();
		AForm();
};
#endif