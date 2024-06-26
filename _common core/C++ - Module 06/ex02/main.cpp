#include <stdint.h>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base *generate(void){
	srand(time(NULL));
	Base *b;
	if(rand()%2==0){
		b=new A();
		return b;
	}else if(rand()%3==0){
		b=new B();
		return b;
	}else{
		b=new C();
		return b;
	}
}

void identify(Base *p){
	if (dynamic_cast<A*>(p))
		std::cout<<"A"<<std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout<<"B"<<std::endl;
	else if(dynamic_cast<C*>(p))
		std::cout<<"C"<<std::endl;
	else if(p==NULL)
		std::cout<<"NULL"<<std::endl;
	else
		std::cout<<"Marshal: Camm'ai dato"<<std::endl;
}

void identify(Base &p) {
	try {
		A& a = dynamic_cast<A&>(p);
		(void)a;
		std::cout << "&A" << std::endl;
		return;
	}catch (const std::exception &e){(void)e;}
	try {
		B& b = dynamic_cast<B&>(p);
		(void)b;
		std::cout << "&B" << std::endl;
		return;
	}catch (const std::exception &e){(void)e;}
	try {
		C& c = dynamic_cast<C&>(p);
		(void)c;
		std::cout << "&C" << std::endl;
		return;
	}catch (const std::exception &e){(void)e;}
	std::cout<<"Marshal: Camm'ai dato"<<std::endl;
}

int main(){
	Base *b=generate();
	identify(*b);
	identify(b);
	return 0;
}