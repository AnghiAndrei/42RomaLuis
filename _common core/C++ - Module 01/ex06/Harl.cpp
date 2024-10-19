#include "Harl.hpp"

void Harl::complain(std::string level){
	std::string text[]={"DEBUG", "INFO", "WARNING", "ERROR", ""};
	int i=0;
	for(;i != 5; i++){
		if(text[i] == level)
			break;
	}
	switch (i) {
		case(0):
			std::cout<<"[ DEBUG ]"<<std::endl;
			debug();
			info();
			warning();
			error();
			break;
		case(1):
			std::cout<<"[ INFO ]"<<std::endl;
			info();
			warning();
			error();
			break;
		case(2):
			std::cout<<"[ WARNING ]"<<std::endl;
			warning();
			error();
			break;
		case(3):
			std::cout<<"[ ERROR ]"<<std::endl;
			error();
			break;
		default:
			std::cout<<"[ Probably complaining about insignificant problems ]"<<std::endl;
			break;
	}
}

void Harl::debug(){std::cout<<"I love having extra bacon for my 7XL-double-cheese-triple-pickle-special ketchup burger. I really do!"<<std::endl;}
void Harl::info(){std::cout<<"I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn’t be asking for more!"<<std::endl;}
void Harl::warning(){std::cout<<"I think I deserve to have some extra bacon for free. I've been coming for years whereas you started working here since last month."<<std::endl;}
void Harl::error(){std::cout<<"This is unacceptable! I want to speak to the manager now."<<std::endl;}