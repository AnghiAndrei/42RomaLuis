#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(std::string target) : AForm("RobotomyRequestForm", 72, 45)
{
	this->target = target;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &toCopy) : AForm(toCopy.getName(), toCopy.getGradeSign(), toCopy.getGradeExecute())
{
	this->target = toCopy.target;
	return;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &toCopy)
{
	if (this != &toCopy)
	{
		this->setSigned(toCopy.getSigned());
		this->target = toCopy.getTarget();
	}
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm()
{
	std::cout << "Called RobotomyRequestForm destructor" << std::endl;
}

std::string RobotomyRequestForm::getTarget() const
{
	return this->target;
}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
	this->checkExecute(executor);
	srand(time(NULL));
	int successRate = rand() % 2;

	if (successRate == 1)
		std::cout << "Napoli Napoli Napoli Forza Napoli Napoli Napoli " << target << " has been robotomized successfully" << std::endl;
	else
		std::cout << "Napoli Napoli Napoli Forza Napoli Napoli Napoli " << target << " has not been robotomized" << std::endl;
}

