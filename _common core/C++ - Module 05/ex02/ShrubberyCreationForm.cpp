#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(std::string name2) : AForm(), grades(145), gradee(137), name(name2){this->signedf=false;}
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &ncopy) : AForm(), grades(ncopy.grades), gradee(ncopy.gradee), name(ncopy.name){this->signedf=ncopy.signedf;}
ShrubberyCreationForm::ShrubberyCreationForm() : grades(1), gradee(1), name("NULL"){this->signedf=false;}
std::string ShrubberyCreationForm::getName() const{return this->name;}
bool ShrubberyCreationForm::getSignedf() const{return this->signedf;}
int ShrubberyCreationForm::getGrades() const{return this->grades;}
int ShrubberyCreationForm::getGradee() const{return this->gradee;}
ShrubberyCreationForm::~ShrubberyCreationForm(){}

ShrubberyCreationForm::ShrubberyCreationForm(std::string name2, int grades2, int gradee2) : grades(grades2), gradee(gradee2), name(name2){
	check_grade(gradee2);
	check_grade(grades2);
	this->signedf=false;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &ncopy){
	this->signedf=ncopy.signedf;
	return *this;
}

void ShrubberyCreationForm::execute(const Bureaucrat &pol) const{
	if(this->signedf==true){
		if(pol.getGrade() <= this->gradee){
			pol.executeForm(this->getName());
			char fileout[this->getName().length() + strlen("_shrubbery") + 1];
			strcpy(fileout, this->getName().c_str());
			strcat(fileout, "_shrubbery");
			std::ofstream f(fileout);
			if (!f.is_open())
				throw FileOpenException();
			std::string text_file=" ()\n(  )\n ||";
			f.write(text_file.c_str(), text_file.length());
			f.close();
		}else
			throw GradeTooLowException();
	}else
		throw FormNotFirmedException();
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