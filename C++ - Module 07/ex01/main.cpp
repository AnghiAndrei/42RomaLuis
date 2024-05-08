#include "iter.hpp"
#include <string.h>

int main(){
	std::string ar[]={"Voglio", "mangiare", "il", "tuo", "pancreas"};
	iter(ar, 5, ft<std::string>);
	int ar2[]={1,2,3,4,5,6,7,8,9};
	iter(ar2, 10, ft<int>);
	return 0;
}
