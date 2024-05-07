#include "AForm.hpp"

std::ostream &operator<<(std::ostream &stream, const AForm &f){return (stream<<"Name Aform: "<<f.getName()<<"\nSigned: "<<f.getSignedf()<<"\nGrade to sign: "<<f.getGrades()<<"\nGrade to execute: "<<f.getGradee()<<std::endl);}
AForm::AForm(const AForm &ncopy) : grades(ncopy.grades), gradee(ncopy.gradee), name(ncopy.name){this->signedf=ncopy.signedf;}
AForm::AForm() : grades(1), gradee(1), name("NULL"){this->signedf=false;}
std::string AForm::getName() const{return this->name;}
bool AForm::getSignedf() const{return this->signedf;}
int AForm::getGrades() const{return this->grades;}
int AForm::getGradee() const{return this->gradee;}
AForm::~AForm(){};

void AForm::check_grade(int grade){
	if (grade > 150)
		throw GradeTooLowException();
	else if(grade < 1)
		throw GradeTooHighException();
}

void AForm::beSigned(const Bureaucrat &pol){
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

AForm::AForm(std::string name2, int grades2, int gradee2) : grades(grades2), gradee(gradee2), name(name2){
	check_grade(gradee2);
	check_grade(grades2);
	this->signedf=false;
}

AForm &AForm::operator=(const AForm &ncopy){
	this->signedf=ncopy.signedf;
	return *this;
}