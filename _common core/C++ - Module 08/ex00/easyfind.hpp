#include <algorithm>
#include <iostream>
#include <vector>

template<typename T>
int easyFind(T& vec, int ago){
	std::vector<int>::iterator temp = std::find(vec.begin(), vec.end(), ago);
	if(temp!=vec.end())
		return 1;
	else
		return -1;
}