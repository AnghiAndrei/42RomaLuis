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
	if((*list).size()==1)
		return ;
	int npend=1;
	size_t pend=2;
	size_t iorder=0;
	for (pend=2;pend<(*list).size()+1;pend=pend*2){
		if(pend!=2)npend=pend/2;
		for (size_t i=0; i<=(*list).size();i+=pend){
			if((*list).size()<=i+pend-npend)
				break;
			if((*list)[i] < (*list)[i+pend-npend]){
				for (size_t v=0;v!=pend-npend;v++){
					if(i+pend-npend+v<(*list).size()){
						int temp=(*list)[i+pend-npend+v];
						(*list)[i+pend-npend+v]=(*list)[i+v];
						(*list)[i+v]=temp;
					}
				}
			}
		}
	}
	pend=pend/2;
	size_t pendm=pend;

	T order;
	for(size_t i=0;(*list).size()!=i;i++)
		order.push_back(-1);
	for(pend=pend;pend!=0;pend=pend/2){
		if(pend!=1){
			npend=0;
			if(pendm==pend)npend=pend/2;
			for(size_t i=0;i<=(*list).size()+1;i+=pend){
				if((*list).size()<=i+pend-npend)
					break;
				for (size_t v=0;v!=pend-npend;v++){
					if(i+pend-npend+v<(*list).size()){
						int temp=(*list)[i+pend-npend+v];
						(*list)[i+pend-npend+v]=(*list)[i+v];
						(*list)[i+v]=temp;
					}
				}
			}
		}
		if(pend==pendm){
			for (size_t i=0;(*list).size()-((*list).size()-(((*list).size()/pend)*pend))>i;i+=(pend/2)){
				order[iorder]=(*list)[i];
				iorder++;
			}
		}else{
			size_t jacobs=calculateJacobs(1), njacobs=2;
			size_t n_cicle=0;
			if(pend!=1)
				for(size_t i=0;(*list).size()-((*list).size()-(((*list).size()/pend)*pend))>i;i+=(pend/2))
					n_cicle++;
			else
				n_cicle=(*list).size();

			size_t i=0;
			for (size_t ncicle=0;ncicle!=n_cicle;ncicle++){
				size_t i3=iorder/2;
				bool flagp=false, flagg=false, zero=false, max=false, inversione=false;

				while(1){
					size_t i3=0;
					while((*list).size()-((*list).size()-(((*list).size()/pend)*pend))>i){
						if(easyFind(order, (*list)[i])==1){
							i+=pend;
							continue;
						}
						if(jacobs-1==i3)
							break;
						i+=pend;
					}
					if(jacobs-1==i3 || (*list).size()==2)
						break;
					else if(jacobs!=0)
						jacobs--;
					if(jacobs<=ncicle || jacobs==0){
						jacobs=calculateJacobs(njacobs);
						njacobs++;
					}
					while(jacobs>n_cicle)
						jacobs--;
				}
				if(i==(*list).size())
					continue;
				while(1){
					if(easyFind(order, (*list)[i])==1)
						break;
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
								if(i3==1){
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
					if(max==true){;}
					if(zero==true)
						i3++;
					for (size_t v=iorder;v!=i3;v--){
						int temp=order[v-1];
						order[v-1]=order[v];
						order[v]=temp;
					}
					order[i3]=(*list)[i];
					iorder++;
					break;
				}
			}
		}
	}
	for (size_t i=0;(*list).size()+1!=i;i++)
		(*list)[i]=order[i];
}
#endif