#include"webserv.hpp"

server::server(webserv &master){
    std::ostringstream cy;
    cy << master.get_n_server() + 1;
    std::string n_server = cy.str();
	error404="./dsite/404.html";
	error418="./dsite/418.html";
	root_assets="./dsite";
    name_server="Server"+n_server;
	index="index.html";
    root="./dsite";
    showdir="yes";
    body_size="";
    host="";
    port=-1;
}

int setnblocking(int socket) {
    int flags=fcntl(socket, F_GETFL, 0);
    if(flags==-1){
		std::cout<<"Marshal: Fcntl failed"<<std::endl;
        exit(-1);
    }
    flags |= O_NONBLOCK;
    if (fcntl(socket, F_SETFL, flags) == -1) {
        std::cout<<"Marshal: Fcntl failed"<<std::endl;
        exit(-1);
    }
    return 0;
}