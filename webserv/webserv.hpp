#ifndef WEBSERV_HPP
#define WEBSERV_HPP
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<sstream>
#include<string>
#include<vector>

class webserv;

class server{
	private:
		std::string name_server;
	public:
		server(webserv &master);

		void set_name(std::string &copy){name_server=copy;}
		std::string get_name(){return name_server;}
};

class webserv{
	private:
		std::vector<server> servers;
	public:
		size_t	get_n_server(){return servers.size();}
		void	crea_server(){servers.push_back(server(*this));}
		~webserv(){}
		webserv(){}
};

server::server(webserv &master) {
    std::ostringstream cy;
    cy << master.get_n_server() + 1;
    std::string n_server = cy.str();
    name_server = "Server " + n_server;
}
#endif