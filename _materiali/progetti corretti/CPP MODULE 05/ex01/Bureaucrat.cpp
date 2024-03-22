#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(std::string name, int grade) : name(name)
{
	if(grade > 150)
		throw GradeTooLowException();
	else if(grade < 1)
		throw GradeTooHighException();
	this->grade = grade;
	std::cout<<"Created with default constructor:\n"<<*this;
}

Bureaucrat::Bureaucrat(const Bureaucrat &toCopy) : name(toCopy.name)
{
	this->grade = toCopy.grade;
	return ;
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &toCopy)
{
	if(this != &toCopy)
		this->grade = toCopy.grade;
	return *this;
}

Bureaucrat::~Bureaucrat()
{
}

std::string Bureaucrat::getName() const
{
	return this->name;
}

int Bureaucrat::getGrade() const
{
	return this->grade;
}

void Bureaucrat::upGrade(int amount)
{
	if(grade - amount > 150)
		throw GradeTooLowException();
	else if(grade - amount < 1)
		throw GradeTooHighException();
	this->grade-=amount;
	std::cout<<"UpGraded, review: \n"<<*this;
}

void Bureaucrat::downGrade(int amount)
{
		if(grade + amount > 150)
		throw GradeTooLowException();
	else if(grade + amount < 1)
		throw GradeTooHighException();
	this->grade+=amount;
	std::cout<<"DownGraded, review: \n"<<*this;
}

void Bureaucrat::signForm(Form &form)
{
	try
	{
		if(form.beSigned(*this))
			std::cout<<this->getName()<<" signed "<<form.getName()<<std::endl;
	}
	catch(std::exception& e)
	{
		std::cerr <<this->getName()<<" couldn't sign "<<form.getName()<<" because "<<e.what()<<"\n";
	}
}

std::ostream&	operator<<(std::ostream& os, const Bureaucrat& bureaucrat)
{
	os << bureaucrat.getName() << ", bureaucrat grade "<<bureaucrat.getGrade()<<std::endl;
	return os;
}

