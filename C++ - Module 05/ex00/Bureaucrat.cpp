#include "Bureaucrat.hpp"

void Bureaucrat::check_grade(int grade){
	if (grade > 150)
		throw GradeTooLowException();
	else if(grade < 1)
		throw GradeTooHighException();
}

std::ostream &operator<<(std::ostream &stream, const Bureaucrat &bc){return (stream << bc.name << ", bureaucrat grade "<<bc.grade<<std::endl);}
Bureaucrat::Bureaucrat(const Bureaucrat &ncopy) : name(ncopy.name){this->grade=ncopy.grade;}
Bureaucrat::Bureaucrat() : name(NULL){this->grade=1;}
Bureaucrat::~Bureaucrat(){};

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &ncopy){
	check_grade(ncopy.grade);
	this->grade=ncopy.grade;
	return *this;
}

Bureaucrat::Bureaucrat(std::string name2, int grade2) : name(name2){
	check_grade(grade2);
	this->grade=grade2;
}

void Bureaucrat::downGrade(int grade){
	if (this->grade + grade > 150)
		throw GradeTooLowException();
	else if(this->grade + grade < 1)
		throw GradeTooHighException();
	this->grade=this->grade+grade;
}

void Bureaucrat::upGrade(int grade){
	if (this->grade - grade > 150)
		throw GradeTooLowException();
	else if(this->grade - grade < 1)
		throw GradeTooHighException();
	this->grade=this->grade-grade;
}