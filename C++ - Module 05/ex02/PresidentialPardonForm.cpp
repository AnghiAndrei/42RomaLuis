#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(std::string name2) : AForm(), grades(25), gradee(5), name(name2){this->signedf=false;}
PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &ncopy) : AForm(), grades(ncopy.grades), gradee(ncopy.gradee), name(ncopy.name){this->signedf=ncopy.signedf;}
PresidentialPardonForm::PresidentialPardonForm() : grades(1), gradee(1), name("NULL"){this->signedf=false;}
std::string PresidentialPardonForm::getName() const{return this->name;}
bool PresidentialPardonForm::getSignedf() const{return this->signedf;}
int PresidentialPardonForm::getGrades() const{return this->grades;}
int PresidentialPardonForm::getGradee() const{return this->gradee;}
PresidentialPardonForm::~PresidentialPardonForm(){}

PresidentialPardonForm::PresidentialPardonForm(std::string name2, int grades2, int gradee2) : grades(grades2), gradee(gradee2), name(name2){
	check_grade(gradee2);
	check_grade(grades2);
	this->signedf=false;
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &ncopy){
	this->signedf=ncopy.signedf;
	return *this;
}

void PresidentialPardonForm::execute(const Bureaucrat &pol) const{
	if(this->signedf==true){
		if(pol.getGrade() <= this->gradee){
			pol.executeForm(this->getName());
			std::cout <<this->getName()<<" has been pardoned by Zaphod Beeblebrox"<<std::endl;
		}else
			throw GradeTooLowException();
	}else
		throw FormNotFirmedException();
}

void PresidentialPardonForm::beSigned(const Bureaucrat &pol){
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