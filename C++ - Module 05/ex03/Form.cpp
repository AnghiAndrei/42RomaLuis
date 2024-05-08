#include "Form.hpp"

std::ostream &operator<<(std::ostream &stream, const Form &f){return (stream<<"Name form: "<<f.getName()<<"\nSigned: "<<f.getSignedf()<<"\nGrade to sign: "<<f.getGrades()<<"\nGrade to execute: "<<f.getGradee()<<std::endl);}
Form::Form(const Form &ncopy) : grades(ncopy.grades), gradee(ncopy.gradee), name(ncopy.name){this->signedf=ncopy.signedf;}
Form::Form() : grades(1), gradee(1), name("NULL"){this->signedf=false;}
std::string Form::getName() const{return this->name;}
bool Form::getSignedf() const{return this->signedf;}
int Form::getGrades() const{return this->grades;}
int Form::getGradee() const{return this->gradee;}
Form::~Form(){};

void Form::check_grade(int grade){
	if (grade > 150)
		throw GradeTooLowException();
	else if(grade < 1)
		throw GradeTooHighException();
}

void Form::beSigned(const Bureaucrat &pol){
	try
	{
		if (this->signedf == false)
		{
			if (pol.getGrade() <= this->grades){
				pol.signForm(this->getName());
				this->signedf=true;
			}
			else
				throw GradeTooLowException();
		}
	}
	catch (const std::exception &e){
		std::cerr<<pol.getName()<<" couldn't sign "<<this->getName()<<" because "<< e.what() << std::endl;
	}
}

Form::Form(std::string name2, int grades2, int gradee2) : grades(grades2), gradee(gradee2), name(name2){
	check_grade(gradee2);
	check_grade(grades2);
	this->signedf=false;
}

Form &Form::operator=(const Form &ncopy){
	this->signedf=ncopy.signedf;
	return *this;
}