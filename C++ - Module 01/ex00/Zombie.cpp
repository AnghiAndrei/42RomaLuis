#include "Zombie.h"

void Zombie::announce(){
    std::cout<<this.name<<": BraiiiiiiinnnzzzZ..."<<endl;
}

Zombie::Zombie(std::string name2){
    this.name=name2;
}

Zombie::~Zombie(){
    std::cout<<this.name<<endl;
}