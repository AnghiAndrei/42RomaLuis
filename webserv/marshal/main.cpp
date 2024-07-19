#include"../webserv.hpp"

void printWebserv(webserv &ws);

int main(int argc, char **argv){
	webserv webservv;
	if(check(argc, argv, &webservv)==-1)
		return -1;
	printWebserv(webservv);
    return 0;
}