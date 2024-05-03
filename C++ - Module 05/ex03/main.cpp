#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(){
	try
	{
		Bureaucrat berluscuni("Berluscuni", 10);
		Form p1("Ponte sullo stretto di messina", 1, 1);
		std::cout<<p1<<std::endl;
		p1.beSigned(berluscuni);
		std::cout<<p1<<std::endl;
	}
	catch (const std::exception &e){
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	return 0;
}