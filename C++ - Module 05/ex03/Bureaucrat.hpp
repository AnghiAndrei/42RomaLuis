#ifndef BUCEAUCRAT_HPP
#define BUCEAUCRAT_HPP
#include <string.h>
#include <iostream>
#include <exception>
class Bureaucrat{
	const std::string name;
	int grade;

	class GradeTooHighException : public std::exception{
		public:
			const char *what() const throw(){return "Grade too high\n";}
	};

	class GradeTooLowException : public std::exception{
		public:
			const char *what() const throw(){return "Grade too low\n";}
	};

	public:
		friend std::ostream &operator<<(std::ostream &stream, const Bureaucrat &Bureaucrat);
		void executeForm(const std::string &formn) const;
		Bureaucrat &operator=(const Bureaucrat &nccopy);
		void signForm(const std::string &formn) const;
		Bureaucrat(std::string name2, int grade2);
		void setName(const Bureaucrat& ncopy);
		Bureaucrat(const Bureaucrat &nccopy);
		std::string getName() const;
		void check_grade(int grade);
		void downGrade(int grade);
		void upGrade(int grade);
		int getGrade() const;
		~Bureaucrat();
		Bureaucrat();
};
#endif