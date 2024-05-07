#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(std::string name2) : AForm(), grades(72), gradee(45), name(name2){this->signedf=false;}
RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &ncopy) : AForm(), grades(ncopy.grades), gradee(ncopy.gradee), name(ncopy.name){this->signedf=ncopy.signedf;}
RobotomyRequestForm::RobotomyRequestForm() : grades(1), gradee(1), name("NULL"){this->signedf=false;}
std::string RobotomyRequestForm::getName() const{return this->name;}
bool RobotomyRequestForm::getSignedf() const{return this->signedf;}
int RobotomyRequestForm::getGrades() const{return this->grades;}
int RobotomyRequestForm::getGradee() const{return this->gradee;}
RobotomyRequestForm::~RobotomyRequestForm(){}

RobotomyRequestForm::RobotomyRequestForm(std::string name2, int grades2, int gradee2) : grades(grades2), gradee(gradee2), name(name2){
	check_grade(gradee2);
	check_grade(grades2);
	this->signedf=false;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &ncopy){
	this->signedf=ncopy.signedf;
	return *this;
}

void RobotomyRequestForm::execute(const Bureaucrat &pol) const{
	if(this->signedf==true){
		if(pol.getGrade() <= this->gradee){
			pol.executeForm(this->getName());
			srand(time(NULL));
			if(rand()%2==0)
				std::cout <<this->getName()<<" has not been robotomized"<<std::endl;
			else
				std::cout <<this->getName()<<" has been robotomized successfully"<<std::endl;
		}else
			throw GradeTooLowException();
	}else
		throw FormNotFirmedException();
}

void RobotomyRequestForm::beSigned(const Bureaucrat &pol){
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