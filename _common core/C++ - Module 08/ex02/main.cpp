#include "MutantStack.hpp"

int main(){
	std::cout<<"Test con int"<<std::endl;
	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout<<"Ultimo aggiunto: "<<mstack.top()<<std::endl;
	mstack.pop();
	std::cout<<"Penultino aggiunto: "<<mstack.top()<<std::endl;
	std::cout<<"Size: "<<mstack.size()<<std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	std::cout<<"Lista di numeri:"<<std::endl;
	while (it != ite){
		std::cout<<*it<<std::endl;
		++it;
	}
	MutantStack<int>::reverse_iterator itr = mstack.rbegin();
	MutantStack<int>::reverse_iterator iter = mstack.rend();
	++itr;
	--itr;
	std::cout<<"Lista di numeri reverse:"<<std::endl;
	while (itr != iter){
		std::cout<<*itr<<std::endl;
		++itr;
	}
	std::stack<int> s(mstack);
	MutantStack<int> exStack;
	try{exStack.pop();}catch(const std::exception& e){std::cout<<e.what()<<std::endl;}
	try{exStack.top();}catch(const std::exception& e){std::cout<<e.what()<<std::endl;}

	MutantStack<int> stackvuoto;
	std::cout<<"Lista vuota:"<<std::endl;
	for (MutantStack<int>::iterator itv=stackvuoto.begin(); itv!=stackvuoto.end(); itv++){std::cout<<*itv<<std::endl;}

	std::cout<<"Test con std::string"<<std::endl;
	MutantStack<std::string> mstack2;
	mstack2.push("Hola");
	mstack2.push("gente");
	std::cout<<"Ultimo aggiunto: "<<mstack2.top()<<std::endl;
	mstack2.pop();
	std::cout<<"Penultino aggiunto: "<<mstack2.top()<<std::endl;
	std::cout<<"Size: "<<mstack2.size()<<std::endl;
	mstack2.pop();
	mstack2.push("Voglio ");
	mstack2.push("mangiare ");
	mstack2.push("il ");
	mstack2.push("tuo ");
	mstack2.push("pancreas!");
	MutantStack<std::string>::iterator its = mstack2.begin();
	MutantStack<std::string>::iterator ites = mstack2.end();
	++its;
	--its;
	std::cout<<"Lista di stringhe:"<<std::endl;
	while (its != ites){
		std::cout<<*its<<std::endl;
		++its;
	}
	MutantStack<std::string>::reverse_iterator itrs = mstack2.rbegin();
	MutantStack<std::string>::reverse_iterator iters = mstack2.rend();
	++itrs;
	--itrs;
	std::cout<<"Lista di stringhe reverse:"<<std::endl;
	while (itrs != iters){
		std::cout<<*itrs<<std::endl;
		++itrs;
	}
	// MutantStack<std::string> exStack2;
	// try{exStack2.pop();}catch(const std::exception& e){std::cout<<e.what()<<std::endl;}
	// try{exStack2.top();}catch(const std::exception& e){std::cout<<e.what()<<std::endl;}

	MutantStack<std::string> stackvuoto2;
	std::cout<<"Lista vuota:"<<std::endl;
	for (MutantStack<std::string>::iterator itv=stackvuoto2.begin(); itv!=stackvuoto2.end(); itv++){std::cout<<*itv<<std::endl;}
	return 0;
}