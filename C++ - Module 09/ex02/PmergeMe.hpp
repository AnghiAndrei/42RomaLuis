#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <ctime>
#include <deque>

// int dimenzione_rimanenti((*list).size()/pend)*pend-(*list).size()

template<typename T>
void sort(T *list){
	std::cout<<std::endl;
	for (size_t i=0;(*list).size()>i;i+=2){
		// std::cout<<"i:"<<i<<"["<<(*list)[i]<<"]"<<" | "<<"i2:"<<i+1<<"["<<(*list)[i+1]<<"]"<<" | "<<"pend: 2"<<std::endl;
		if((*list)[i] > (*list)[i+1] && i+1<(*list).size()){
			// std::cout<<"Swap coppie: "<<i<<"["<<(*list)[i]<<"]"<<" | "<<"i2:"<<i+1<<"["<<(*list)[i+1]<<"]"<<std::endl;
			int temp=(*list)[i+1];
			(*list)[i+1]=(*list)[i];
			(*list)[i]=temp;
		}
	}
	std::cout<<"Pend 2: ";
	for (size_t i=0;(*list).size()!=i;i++){
		if(i%2==0)std::cout<<"| ";
		std::cout<<(*list)[i]<<" ";
	}
	std::cout<<"|"<<std::endl<<std::endl;

	for (size_t i=1;(*list).size()>i;i+=2){
		std::cout<<"i:"<<i<<"["<<(*list)[i]<<"]"<<" | "<<"i2:"<<i+2<<"["<<(*list)[i+2]<<"]"<<" | "<<"pend: 2"<<std::endl;
		if((*list)[i] > (*list)[i+2] && i+2<(*list).size()){
			std::cout<<"Swap coppie: "<<i<<"["<<(*list)[i]<<"]"<<" | "<<"i2:"<<i+2<<"["<<(*list)[i+2]<<"]"<<std::endl;
			int temp=(*list)[i+2];
			(*list)[i+2]=(*list)[i];
			(*list)[i]=temp;
		}
	}
	std::cout<<"Pend 4: ";
	for (size_t i=0;(*list).size()!=i;i++){
		if(i%4==0)std::cout<<"| ";
		std::cout<<(*list)[i]<<" ";
	}
	std::cout<<"|"<<std::endl<<std::endl;



	std::cout<<std::endl;
	std::cout<<"Lista pesi m.: ";
	for (size_t i=0;(*list).size()>i;i+=2)
		std::cout<<(*list)[i]<<" ";
	std::cout<<std::endl<<std::endl;
}

#endif