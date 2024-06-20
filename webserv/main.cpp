#include"webserv.hpp"

int main(int argc, char **argv){
    std::string conffile;
    if(argc>=2){
        std::cout<<"Marshal: numero di argomenti sbagliato"<<std::endl;
        return -1;
    }else if(argc==1)
        conffile="./default.conf";
    else
        conffile=argv[1];
    std::cout<<conffile<<std::endl;
    return 0;
}