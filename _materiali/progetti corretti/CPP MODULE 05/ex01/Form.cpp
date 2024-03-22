/*The grades of the Form follow the same rules that apply to the Bureaucrat. Thus,
the following exceptions will be thrown if a form grade is out of bounds:
Form::GradeTooHighException and Form::GradeTooLowException.
Same as before, write getters for all attributes and an overload of the insertion («)
operator that prints all the form’s informations.


Add also a beSigned() member function to the Form that takes a Bureaucrat as
parameter. It changes the form status to signed if the bureaucrat’s grade is high enough
(higher or egal to the required one). Remember, grade 1 is higher than grade 2.
If the grade is too low, throw a Form::GradeTooLowException.
Lastly, add a signForm() member function to the Bureaucrat. If the form got signed,
it will print something like:
<bureaucrat> signed <form>
Otherwise, it will print something like:
<bureaucrat> couldn’t sign <form> because <reason>.
Implement and turn in some tests to ensure everything works as expected.*/

#include "Form.hpp"

Form::Form(std::string name, int const gradeSign, int const gradeExecute) : _name(name), _signed(false), _gradeSign(gradeSign), _gradeExecute(gradeExecute)
{
	if (gradeExecute > 150 || gradeSign > 150)
		throw Form::GradeTooLowException();
	else if (gradeExecute < 1 || gradeSign < 1)
		throw Form::GradeTooHighException();
	std::cout << "Created with default constructor:\n"
			  << *this;
}
Form::Form(const Form &toCopy) : _name(toCopy.getName()), _signed(toCopy.getSigned()), _gradeSign(toCopy.getGradeSign()), _gradeExecute(toCopy.getGradeExecute())
{
	std::cout << "Created with copy constructor:\n"
			  << *this;
}
Form &Form::operator=(const Form &toCopy)
{
	if (this != &toCopy)
		this->_signed = toCopy.getSigned();
	return *this;
}

Form::~Form()
{
}

bool Form::beSigned(Bureaucrat const &bure)
{
	if (this->_signed == true)
	{
		std::cout << "Form alredy signed" << std::endl;
		return false;
	}
	if (bure.getGrade() > this->getGradeSign())
		throw Form::GradeTooLowException();
	else
		this->_signed = true;
	return true;
}
bool Form::getSigned() const
{
	return this->_signed;
}
int Form::getGradeSign() const
{
	return this->_gradeSign;
}
int Form::getGradeExecute() const
{
	return this->_gradeExecute;
}
std::string Form::getName() const
{
	return this->_name;
}

std::ostream &operator<<(std::ostream &os, const Form &form)
{
	os << form.getName() << ", grade to be signed " << form.getGradeSign() << ", grade to be executed " << form.getGradeExecute() << ", signed: " << form.getSigned() << std::endl;
	return os;
}
