#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <ctime>
#include <deque>

int calculateJacobs(int n);
// int dimenzione_rimanenti((*list).size()/pend)*pend-(*list).size()

template<typename T>
int easyFind(T& vec, int ago){
	for (size_t i=0;i!=vec.size();i++){
		if(vec[i]==ago)
			return 1;
	}
	return -1;
}

template<typename T>
void sort(T *list){
	std::cout<<std::endl;
	int npend=1;
	size_t pend=2;
	size_t iorder=0;
	for (pend=2;pend<(*list).size()+1;pend=pend*2){
		if(pend!=2)npend=pend/2;
		for (size_t i=0; i<=(*list).size();i+=pend){
			if((*list).size()<=i+pend-npend)
				break;
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
	std::cout<<std::endl<<std::endl;

	T order;
	for(size_t i=0;(*list).size()!=i;i++)
		order.push_back(-1);
	for(pend=pend;pend!=1;pend=pend/2){
		npend=0;
		if(pendm==pend)npend=pend/2;
		for(size_t i=0;i<=(*list).size()+1;i+=pend){
			if((*list).size()<=i+pend-npend)
				break;
			// std::cout<<"i:"<<i<<"["<<(*list)[i]<<"]"<<" | "<<"i2:"<<i+pend-npend<<"["<<(*list)[i+pend-npend]<<"]"<<" | "<<"pend: "<<pend<<std::endl;
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
			// std::cout<<"! Inserimento primi numeri in lista ordinata !"<<std::endl;
			for (size_t i=0;(*list).size()-((*list).size()-(((*list).size()/pend)*pend))>i;i+=(pend/2)){
				order[iorder]=(*list)[i];
				iorder++;
			}
		}else{
			size_t n_cicle=0;
			for(size_t i=0;(*list).size()-((*list).size()-(((*list).size()/pend)*pend))>i;i+=(pend/2))
				n_cicle++;

			size_t jacobs=calculateJacobs(0);
			size_t mjacobs=jacobs;
			size_t njacobs=1;
			for (size_t ncicle=0;ncicle!=n_cicle;ncicle++){
				size_t i=0;
				jacobs++;
				ncicle--;
				do{
					jacobs--;
					ncicle++;
					if(jacobs==mjacobs && mjacobs!=1){
						mjacobs=calculateJacobs(njacobs-1);
						jacobs=calculateJacobs(njacobs);
						njacobs++;
					}
					while(jacobs<=(*list).size())
						jacobs--;
					for(size_t i3=0;jacobs!=i3 && (*list).size()-((*list).size()-(((*list).size()/pend)*pend))>i;i3++)
						i+=(pend/2);
				}while(easyFind(order, (*list)[i])==-1);
				if(i==(*list).size())
					continue;
				std::cout<<"i: "<<i<<std::endl;
				std::cout<<"Jacobs: "<<jacobs<<std::endl;

				size_t i3=iorder/2;
				bool flagp=false, flagg=false, zero=false, max=false, inversione=false;

				if(easyFind(order, (*list)[i])!=1){
					std::cout<<std::endl<<"Lista order: ";
					for (size_t i5=0;order.size()!=i5;i5++)
						std::cout<<order[i5]<<" ";
					std::cout<<std::endl;
					std::cout<<"Da inserire: "<<(*list)[i]<<std::endl;
				}

				while(1){
					// std::cout<<"i3 pre-insert: "<<i3<<std::endl;
					if(i3!=iorder){
						if(inversione==true || i3==0){
							if(flagg==false && (*list)[i]<order[i3]){
								flagp=true;
								if(i3==0)
									zero=false;
								else{
									zero=true;
									i3--;
									continue;
								}
							}else if (flagp==false && (*list)[i]>order[i3]){
								flagg=true;
								if(i3==iorder)
									max=false;
								else{
									max=true;
									i3++;
									continue;
								}
							}
						}else{
							if(flagg==false && (*list)[i]<order[i3]){
								flagp=true;
									zero=true;
									i3=(i3/2);
									continue;
							}else if (flagp==false && (*list)[i]>order[i3]){
								flagg=true;
								max=true;
								if(i3==2){
									inversione=true;
									flagp=false;
									flagg=false;
									zero=false;
									max=false;
									continue;
								}
									i3=i3+(iorder-i3)/2;
								continue;
							}else{
								inversione=true;
								flagp=false;
								flagg=false;
								zero=false;
								max=false;
								continue;
							}
						}
					}
					if(zero==true)
						i3++;
					for (size_t v=iorder;v!=i3;v--){
						int temp=order[v-1];
						order[v-1]=order[v];
						order[v]=temp;
					}
					order[i3]=(*list)[i];
					iorder++;
					// std::cout<<"i3: "<<i3<<std::endl;
					break;
				}
				jacobs--;
			}
		}
		// std::cout<<"Lista order: ";
		// for (size_t i5=0;order.size()!=i5;i5++)
		// 	std::cout<<order[i5]<<" ";
		// std::cout<<std::endl;

		// std::cout<<"Lista swap: ";
		// for (size_t i=0;(*list).size()!=i;i++){
		// 	if(i%pend==0)std::cout<<"| ";
		// 	std::cout<<(*list)[i]<<" ";
		// }
		// std::cout<<std::endl<<std::endl;
	}
	for (size_t i=0;(*list).size()+1!=i;i++)
		(*list)[i]=order[i];
}

#endif