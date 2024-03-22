#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : AForm("ShrubberyCreationForm", 145, 137)
{
	this->target = target;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &toCopy) : AForm(toCopy.getName(), toCopy.getGradeSign(), toCopy.getGradeExecute())
{
	this->target = toCopy.target;
	return;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &toCopy)
{
	if (this != &toCopy)
	{
		this->setSigned(toCopy.getSigned());
		this->target = toCopy.getTarget();
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
	std::cout << "Called ShrubberyCreationForm destructor" << std::endl;
}

std::string ShrubberyCreationForm::getTarget() const
{
	return this->target;
}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	this->checkExecute(executor);
	std::string tree =
		"        *\n"
		"       / \\\n"
		"      /   \\\n"
		"     /     \\\n"
		"    /       \\\n"
		"   /         \\\n"
		"  /___________\\\n"
		"      |   |\n"
		"      |   |\n"
		"      |___|\n"
		"      /   \\\n"
		"     /     \\\n"
		"    /       \\\n"
		"   /         \\\n"
		"  /___________\\\n"
		"      |   |\n"
		"      |   |\n"
		"      |___|\n";
	std::string filename = this->getTarget() + "_shrubbery";
	std::ofstream fileout((filename).c_str());
	if (fileout.is_open())
	{
		for(int i = 0; i < 100; i++)
			fileout << tree;
		fileout.close();
	}
	else
		std::cout << "Errore nell'apertura del file" << std::endl;
}
