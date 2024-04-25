#include <iostream>
#include "AAnimal.hpp"
#include "ADog.hpp"
int main(){
    // const AAnimal* j = new AAnimal();
	// delete j;
	const AAnimal* j = new ADog();
	delete j;
    return 0;
}