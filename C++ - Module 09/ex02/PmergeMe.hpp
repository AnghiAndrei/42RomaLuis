#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <ctime>
#include <deque>

// int dimenzione_rimanenti((*list).size()/pend)*pend-(*list).size()

template<typename T>
int easyFind(T& vec, int ago){
	std::vector<int>::iterator temp = std::find(vec.begin(), vec.end(), ago);
	if(temp!=vec.end())
		return 1;
	else
		return -1;
}

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
	pend=pend/2;
	size_t pendm=pend;
	std::cout<<"Lista intera: ";
	for (size_t i=0;(*list).size()>i;i++)
		std::cout<<(*list)[i]<<" ";
	std::cout<<std::endl;

	std::cout<<std::endl;
	T order;
	for(size_t i=0;(*list).size()!=i;i++)
		order.push_back(-1);
	for(pend=pend;pend!=1;pend=pend/2){
		npend=pend/2;
		for(size_t i=0;i<=(*list).size();i+=pend){
			std::cout<<"i:"<<i<<"["<<(*list)[i]<<"]"<<" | "<<"i2:"<<i+pend-npend<<"["<<(*list)[i+pend-npend]<<"]"<<" | "<<"pend: "<<pend<<std::endl;
			for (size_t v=0;v!=pend-npend;v++){
				if(i+pend-npend+v<(*list).size()){
					// std::cout<<"Swap coppie: "<<i+pend-npend+v<<"["<<(*list)[i+pend-npend+v]<<"]"<<" | "<<"i2:"<<i+v<<"["<<(*list)[i+v]<<"]"<<std::endl;
					int temp=(*list)[i+pend-npend+v];
					(*list)[i+pend-npend+v]=(*list)[i+v];
					(*list)[i+v]=temp;
				}
			}
		}
		if(pend==pendm){
			size_t i2=0;
			for (size_t i=0;(*list).size()-((*list).size()-(((*list).size()/pend)*pend))>i;i+=(pend/2)){
				order[i2]=(*list)[i];
				i2++;
			}
		}
		std::cout<<"Lista swap: ";
		for (size_t i=0;(*list).size()!=i;i++){
			if(i%pend==0)std::cout<<"| ";
			std::cout<<(*list)[i]<<" ";
		}
		std::cout<<std::endl<<std::endl;
	}
	for (size_t i=0;(*list).size()!=i;i++)
		(*list)[i]=order[i];
}

#endif