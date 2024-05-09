#include "Array.hpp"

int main() {
	int *a=new int();
	std::cout<<*a<<std::endl;

    Array<int, 3> ar;
    ar[0] = 1;
    ar[1] = 2;
    ar[2] = 3;
    std::cout<<"Size:"<<ar.size()<<std::endl;
    for (size_t i=0;i!=ar.size();i++)
        std::cout<<i<<": "<<ar[i]<<std::endl;
    return 0;
}