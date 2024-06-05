#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <ctime>
#include <deque>

template<typename T>
void sort(T *list){
	std::cout<<std::endl;
	for (size_t pend=2;pend<=(*list).size();pend=pend*2){
		int npend=1;
		if(pend!=2)npend=pend/2;
		for (size_t i=0; i<(*list).size();i+=pend){
			if((*list).size()-i<pend)break;
			std::cout<<"i:"<<i<<"["<<(*list)[i]<<"]"<<" | "<<"i2:"<<i+pend-npend<<"["<<(*list)[i+pend-npend]<<"]"<<" | "<<"pend: "<<pend<<std::endl;
			if((*list)[i] < (*list)[i+pend-npend]){
				for (size_t v=0;v!=pend-npend;v++){
					int temp=(*list)[i+pend-npend+v];
					(*list)[i+pend-npend+v]=(*list)[i+v];
					(*list)[i+v]=temp;
				}
			}
		}
		std::cout<<"Pend "<<pend<<": ";
		for (size_t i=0;(*list).size()!=i;i++){
			if(i%pend==0)std::cout<<"| ";
			std::cout<<(*list)[i]<<" ";
		}
		std::cout<<"|"<<std::endl<<std::endl;
	}
}

#endif