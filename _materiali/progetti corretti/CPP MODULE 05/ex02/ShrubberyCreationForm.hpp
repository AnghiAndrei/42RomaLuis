
#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP
#include "AForm.hpp"

// Create a file <target>_shrubbery in the working directory, and writes ASCII trees
// inside it.
class ShrubberyCreationForm : public AForm
{
private:
	std::string target;

public:
	ShrubberyCreationForm(std::string target);
	ShrubberyCreationForm(const ShrubberyCreationForm &toCopy);
	ShrubberyCreationForm &operator=(const ShrubberyCreationForm &toCopy);
	~ShrubberyCreationForm();
	virtual void execute(Bureaucrat const &executor) const;
	std::string getTarget() const;
};
#endif
