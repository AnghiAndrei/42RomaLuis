#include"../webserv.hpp"

int main(int argc, char **argv){
	webserv webservv;
	if(check(argc, argv, &webservv)==-1)
		return -1;
    return 0;
}