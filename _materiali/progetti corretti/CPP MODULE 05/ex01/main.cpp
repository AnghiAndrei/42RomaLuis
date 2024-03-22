#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	try
	{
		Bureaucrat bureaucrat("John", 5);

		bureaucrat.upGrade(2);
		bureaucrat.downGrade(1);
		// Proviamo a creare un form e firmarlo
		Form form("Tax Form", 5, 3);
		bureaucrat.signForm(form);
		Form form2("Napoli Form", 5, 3);
		// Proviamo a firmare il form con un grado troppo basso
		Bureaucrat bureaucrat2("Alice", 10);
		bureaucrat2.signForm(form2);
		std::cout<<form;
		std::cout<<form2;
	}
	catch (const std::exception &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	return 0;
}
