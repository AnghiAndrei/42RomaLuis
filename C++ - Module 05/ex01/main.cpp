#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(){
	// try
	// {
	// 	Bureaucrat Mussolini("Mussolini", 1);
	// 	Form p1("Ponte sullo stretto di messina", 150, 150);
	// 	std::cout<<p1<<std::endl;
	// 	p1.beSigned(Mussolini);
	// 	std::cout<<p1<<std::endl;
	// }
	// catch (const std::exception &e){
	// 	std::cerr << "Exception caught: " << e.what() << std::endl;
	// }

	try
	{
		Bureaucrat Mussolini("Mussolini", 10);
		Form p1("Ponte sullo stretto di messina", 1, 1);
		// Form p1("Ponte sullo stretto di messina", 1, 151);
		// Form p1("Ponte sullo stretto di messina", 1, -151);
		// Form p1("Ponte sullo stretto di messina", -151, 1);
		// Form p1("Ponte sullo stretto di messina", 151, 1);
		std::cout<<p1<<std::endl;
		p1.beSigned(Mussolini);
		std::cout<<p1<<std::endl;
	}
	catch (const std::exception &e){
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	return 0;
}