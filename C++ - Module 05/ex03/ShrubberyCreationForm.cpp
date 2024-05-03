#include "ShrubberyCreationForm.hpp"

std::ostream &operator<<(std::ostream &stream, const ShrubberyCreationForm &f){return (stream<<"Name ShrubberyCreationForm: "<<f.getName()<<"\nSigned: "<<f.getSignedf()<<"\nGrade to sign: "<<f.getGrades()<<"\nGrade to execute: "<<f.getGradee()<<std::endl);}
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &ncopy) : grades(ncopy.grades), gradee(ncopy.gradee), name(ncopy.name){this->signedf=ncopy.signedf;}
ShrubberyCreationForm::ShrubberyCreationForm() : grades(1), gradee(1), name("NULL"){this->signedf=false;}
std::string ShrubberyCreationForm::getName() const{return this->name;}
bool ShrubberyCreationForm::getSignedf() const{return this->signedf;}
int ShrubberyCreationForm::getGrades() const{return this->grades;}
int ShrubberyCreationForm::getGradee() const{return this->gradee;}
ShrubberyCreationForm::~ShrubberyCreationForm(){};

void ShrubberyCreationForm::check_grade(int grade){
	if (grade > 150)
		throw GradeTooLowException();
	else if(grade < 1)
		throw GradeTooHighException();
}

void ShrubberyCreationForm::beSigned(const Bureaucrat &pol){
	try
	{
		if (this->signedf == false)
		{
			if (pol.getGrade() <= this->grades){
				this->signedf=true;
				pol.signForm(this->getName());
			}
			else
				throw GradeTooLowException();
		}
	}
	catch (const std::exception &e){
		std::cerr<<pol.getName()<<" couldn't sign "<<this->getName()<<" because "<< e.what() << std::endl;
	}
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string name2, int grades2, int gradee2) : grades(grades2), gradee(gradee2), name(name2){
	check_grade(gradee2);
	check_grade(grades2);
	this->signedf=false;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &ncopy){
	this->signedf=ncopy.signedf;
	return *this;
}