#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(std::string target) : AForm("PresidentialPardonForm", 72, 45)
{
	this->target = target;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &toCopy) : AForm(toCopy.getName(), toCopy.getGradeSign(), toCopy.getGradeExecute())
{
	this->target = toCopy.target;
	return;
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &toCopy)
{
	if (this != &toCopy)
	{
		this->setSigned(toCopy.getSigned());
		this->target = toCopy.getTarget();
	}
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
	std::cout << "Called PresidentialPardonForm destructor" << std::endl;
}

std::string PresidentialPardonForm::getTarget() const
{
	return this->target;
}

void PresidentialPardonForm::execute(Bureaucrat const &executor) const
{
	this->checkExecute(executor);
	std::cout<<this->target<<" has been pardoned by Zaphod Beeblebrox"<<std::endl;
}
