#include "AForm.hpp"

AForm::AForm(std::string name, int const gradeSign, int const gradeExecute) : _name(name), _signed(false), _gradeSign(gradeSign), _gradeExecute(gradeExecute)
{
	if (gradeExecute > 150 || gradeSign > 150)
		throw AForm::GradeTooLowException();
	else if (gradeExecute < 1 || gradeSign < 1)
		throw AForm::GradeTooHighException();
	std::cout << "Created with default constructor:\n"
			  << *this;
}
AForm::AForm(const AForm &toCopy) : _name(toCopy.getName()), _signed(toCopy.getSigned()), _gradeSign(toCopy.getGradeSign()), _gradeExecute(toCopy.getGradeExecute())
{
	std::cout << "Created with copy constructor:\n"
			  << *this;
}
AForm &AForm::operator=(const AForm &toCopy)
{
	if (this != &toCopy)
		this->_signed = toCopy.getSigned();
	return *this;
}

AForm::~AForm()
{
}

bool AForm::beSigned(Bureaucrat const &bure)
{
	if (this->_signed == true)
	{
		std::cout << "Form alredy signed" << std::endl;
		return false;
	}
	if (bure.getGrade() > this->getGradeSign())
		throw AForm::GradeTooLowException();
	else
		this->_signed = true;
	return true;
}

bool AForm::getSigned() const
{
	return this->_signed;
}
int AForm::getGradeSign() const
{
	return this->_gradeSign;
}
int AForm::getGradeExecute() const
{
	return this->_gradeExecute;
}
std::string AForm::getName() const
{
	return this->_name;
}

void AForm::setSigned(bool value)
{
	this->_signed = value;
}

void AForm::checkExecute(Bureaucrat const & executor) const
{
	if (this->getSigned() == false)
		throw AForm::NotSignedException();
	else if (executor.getGrade() > this->getGradeExecute())
		throw AForm::GradeTooLowException();
}

std::ostream &operator<<(std::ostream &os, const AForm &form)
{
	os << form.getName() << ", grade to be signed " << form.getGradeSign() << ", grade to be executed " << form.getGradeExecute() << ", signed: " << form.getSigned() << std::endl;
	return os;
}
