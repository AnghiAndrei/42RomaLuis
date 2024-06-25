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
		std::vector<std::string> med_allow;
		std::string name_server;
		std::string body_size;
		std::string error404;
		std::string error418;
		std::string host;
		std::string port;
	public:
		server(webserv &master);

		void set_body_size(std::string &copy){body_size=copy;}
		void set_error404(std::string &copy){error404=copy;}
		void set_name(std::string &copy){name_server=copy;}
		void set_host(std::string &copy){host=copy;}
		void set_port(std::string &copy){port=copy;}
		std::string get_port(){return port;}
		std::string get_host(){return host;}
		std::string get_name(){return name_server;}
		std::string get_error404(){return error404;}
		std::string get_body_size(){return body_size;}

		void set_error418(std::string &copy){error418=copy;}
		std::string get_error418(){return error418;}

		void set_medallow(std::vector<std::string> copy){this->med_allow.insert(med_allow.begin(), copy.begin(), copy.end());}
		std::string get_medallow(int index){return med_allow[index];}
		size_t get_lmedallow(){return med_allow.size();}
};

class webserv{
	size_t nserv;
	public:
		std::vector<server> servers;

		void crea_server(){servers.push_back(server(*this));}
		size_t	get_n_server(){return servers.size();}
		void set_nserv(size_t serv){this->nserv=serv;}
		~webserv(){}
		webserv(){}
};

server::server(webserv &master) {
    std::ostringstream cy;
    cy << master.get_n_server() + 1;
    std::string n_server = cy.str();
	error404="./pages/error404.html";
	error418="./pages/error418.html";
    name_server="Server"+n_server;
    body_size="";
    host="";
    port="";
}
#endif