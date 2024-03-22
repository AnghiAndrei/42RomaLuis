
#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"
#include <cstdlib>
#include <ctime>

class PresidentialPardonForm : public AForm
{
private:
	std::string target;

public:
	PresidentialPardonForm(std::string target);
	PresidentialPardonForm(const PresidentialPardonForm &toCopy);
	PresidentialPardonForm &operator=(const PresidentialPardonForm &toCopy);
	~PresidentialPardonForm();
	virtual void execute(Bureaucrat const &executor) const;
	std::string getTarget() const;
};


#endif
