#include <iostream>

template <typename T>
void ft (T element){std::cout<<element<<std::endl;}

template <typename T, typename Func>
void iter(T *addr, int lent, Func ft){
    for(int i=0;i!=lent;i++)
        ft(addr[i]);
}