#include "Harl.hpp"

void Harl::complain(std::string level){
    void (Harl::*function[])(void) = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
    std::string text={"DEBUG", "INFO", "WARNING", "ERROR"};
    for(int i=0;i != 4; i++){
        if (level==text[i])
            (this->*function[i])();
    }
}

Harl::void debug(){std::cout<<"I love having extra bacon for my 7XL-double-cheese-triple-pickle-special ketchup burger. I really do!"<<std::endl;}
Harl::void info(){std::cout<<"I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn’t be asking for more!"<<std::endl;}
Harl::void warning(){std::cout<<"I think I deserve to have some extra bacon for free. I've been coming for years whereas you started working here since last month."<<std::endl;}
Harl::void error(){std::cout<<"This is unacceptable! I want to speak to the manager now."<<std::endl;}