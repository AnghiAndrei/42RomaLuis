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
	int npend=1;
	size_t pend=2;
	for (pend=2;pend<(*list).size()+1;pend=pend*2){
		if(pend!=2)npend=pend/2;
		for (size_t i=0; i<=(*list).size();i+=pend){
			// std::cout<<"i:"<<i<<"["<<(*list)[i]<<"]"<<" | "<<"i2:"<<i+pend-npend<<"["<<(*list)[i+pend-npend]<<"]"<<" | "<<"pend: "<<pend<<std::endl;
			if((*list)[i] < (*list)[i+pend-npend]){
				for (size_t v=0;v!=pend-npend;v++){
					if(i+pend-npend+v<(*list).size()){
						// std::cout<<"Swap coppie: "<<i+pend-npend+v<<"["<<(*list)[i+pend-npend+v]<<"]"<<" | "<<"i2:"<<i+v<<"["<<(*list)[i+v]<<"]"<<std::endl;
						int temp=(*list)[i+pend-npend+v];
						(*list)[i+pend-npend+v]=(*list)[i+v];
						(*list)[i+v]=temp;
					}
				}
			}
		}
		// std::cout<<"Pend "<<pend<<": ";
		// for (size_t i=0;(*list).size()!=i;i++){
		// 	if(i%pend==0)std::cout<<"| ";
		// 	std::cout<<(*list)[i]<<" ";
		// }
		// std::cout<<"|"<<std::endl<<std::endl;
	}
	pend=pend/4;
	std::cout<<"Lista intera: ";
	for (size_t i=0;(*list).size()>i;i++)
		std::cout<<(*list)[i]<<" ";
	std::cout<<std::endl;

	std::cout<<std::endl;
	//ogni mimino di ogni coppia deve essere messo nella lista cercardo il suo spazio per ogni meta
	for (pend=pend;pend!=1;pend=pend/2){
		if(pend!=2)npend=pend/2;
		for (size_t i=0; i<=(*list).size();i+=pend){
			std::cout<<"i:"<<i<<"["<<(*list)[i]<<"]"<<" | "<<"i2:"<<i+pend-npend<<"["<<(*list)[i+pend-npend]<<"]"<<" | "<<"pend: "<<pend<<std::endl;
		}
		std::cout<<"Lista ordinata: ";
		for (size_t i=0;(*list).size()-((*list).size()-(((*list).size()/pend)*pend))>i;i+=pend)
			std::cout<<(*list)[i]<<" ";
		std::cout<<std::endl<<std::endl;
	}
	
}

#endif