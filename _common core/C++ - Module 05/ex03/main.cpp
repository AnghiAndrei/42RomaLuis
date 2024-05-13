#include "PresidentialPardonForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "Form.hpp"

int main(){
	try{
		Bureaucrat Mussolini("Mussolini", 1);
		Intern someRandomIntern;
		Form* rrf4=someRandomIntern.makeForm("invalid", "Form3");
		rrf4->beSigned(Mussolini);
		rrf4->execute(Mussolini);
	}catch (const std::exception &e){
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	try
	{
		Bureaucrat Mussolini("Mussolini", 1);
		Intern someRandomIntern;

		Form* rrf1=someRandomIntern.makeForm("robotomy request", "Form1");
		Form* rrf2=someRandomIntern.makeForm("presidential", "Form2");
		Form* rrf3=someRandomIntern.makeForm("shrubbery", "Form3");

		rrf1->beSigned(Mussolini);
		rrf2->beSigned(Mussolini);
		rrf3->beSigned(Mussolini);

		rrf1->execute(Mussolini);
		rrf2->execute(Mussolini);
		rrf3->execute(Mussolini);

		delete rrf1;
		delete rrf2;
		delete rrf3;
	}
	catch (const std::exception &e){
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	return 0;
}