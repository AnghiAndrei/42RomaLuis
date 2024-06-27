#include"webserv.hpp"

server::server(webserv &master){
    std::ostringstream cy;
    cy << master.get_n_server() + 1;
    std::string n_server = cy.str();
	error404="./dsite/404.html";
	error418="./dsite/418.html";
	root_assets="./dsite/Assets/img";
    name_server="Server"+n_server;
	index="index.html";
    root="./dsite/";
    showdir="yes";
    body_size="";
    host="";
    port="";
}