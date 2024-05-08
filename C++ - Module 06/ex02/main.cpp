#include "Date.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base *generate(void){
	srand(time(NULL));
	if(rand()%2==0)
		return new A();
	else if(rand()%3==0){
		return new B();
	}else{
		return new C();
	}
}

void identify(Base& p){
	if (dynamic_cast<A*>(p))
		std::cout<<"A"<<std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout<<"B"<<std::endl;
	else if(dynamic_cast<C*>(p))
		std::cout<<"C"<<std::endl;
	else
		std::cout<<"Marshal: Camm'ai dato"<<std::endl;
}

int main(){
	Base *r=generate();
	identify(r);
	delete r;
	return 0;
}