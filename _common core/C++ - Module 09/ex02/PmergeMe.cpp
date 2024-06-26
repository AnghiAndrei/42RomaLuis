#include "PmergeMe.hpp"

int calculateJacobs(int n){
    if(n==1)return 1;
    if(n==2)return 2;
    if(n==3)return 3;

    int J0=1, J1=2, J2=3, Jn;
    for (int i=3;i<=n;++i){
        Jn=J2+J1+J0;
        J0=J1;
        J1=J2;
        J2=Jn;
    }
    return Jn;
}
