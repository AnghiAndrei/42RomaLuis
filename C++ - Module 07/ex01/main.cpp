#include "iter.hpp"
#include <string.h>

int main(){
	std::string ar[]={"Voglio", "mangiare", "il", "tuo", "pancreas"};
	iter(&ar , 5, sizeof);
	return 0;
}
