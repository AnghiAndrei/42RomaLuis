#include <iostream>
#include <string>

template<typename T[]>
int easyfind(T[], int ago){
    for(int i=0; T[i]!='\0';i++){
        if(T[i]==ago)
            return i;
    }
    std::cout<<"Char not found"<<std::endl;
    return -1;
}