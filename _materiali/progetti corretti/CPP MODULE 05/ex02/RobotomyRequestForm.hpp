
#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"
#include <cstdlib>
#include <ctime>

class RobotomyRequestForm : public AForm
{
private:
	std::string target;

public:
	RobotomyRequestForm(std::string target);
	RobotomyRequestForm(const RobotomyRequestForm &toCopy);
	RobotomyRequestForm &operator=(const RobotomyRequestForm &toCopy);
	~RobotomyRequestForm();
	virtual void execute(Bureaucrat const &executor) const;
	std::string getTarget() const;
};
#endif
