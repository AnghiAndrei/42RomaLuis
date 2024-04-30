#include "Brain.hpp"

Brain::~Brain(){std::cout<<"Brain dead!"<<std::endl;}

Brain::Brain(){
	std::cout<<"Brain install!"<<std::endl;
	for(int i=0; i!=100; i++){
		this->ideas[i]="Food!";
	}
}

Brain &Brain::operator=(Brain &ncopy){
	for(int i=0; i!=100; i++){
		this->ideas[i]=ncopy.ideas[i];
	}
	return *this;
}

Brain::Brain(const Brain &ncopy){
	for(int i=0; i!=100; i++){
		this->ideas[i]=ncopy.ideas[i];
	}
}
