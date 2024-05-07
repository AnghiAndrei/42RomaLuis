#include "PresidentialPardonForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"

int main(){
	try
	{
		Bureaucrat Mussolini("Mussolini", 1);
		ShrubberyCreationForm p1("Ponte sullo stretto di messina");
		p1.beSigned(Mussolini);
		p1.execute(Mussolini);
		RobotomyRequestForm p2("Supporto alla Ucraina");
		p2.beSigned(Mussolini);
		p2.execute(Mussolini);
		PresidentialPardonForm p3("Invasione della palestina");
		p3.beSigned(Mussolini);
		p3.execute(Mussolini);
	}
	catch (const std::exception &e){
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	return 0;
}