#ifndef WEBSERV_HPP
#define WEBSERV_HPP
#include<algorithm>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<sstream>
#include<string>
#include<vector>

class webserv;

int check(int argc, char **argv, webserv *webservv);

class server{
	private:
		std::vector<std::string> med_allow;
		std::vector<std::string> ridirect;
		std::string root_assets;
		std::string name_server;
		std::string body_size;
		std::string error404;
		std::string error418;
		std::string showdir;
		std::string index;
		std::string host;
		std::string root;
		std::string port;

	public:
		server(webserv &master);

		void set_root_assets(std::string &copy){root_assets=copy;}
		void set_body_size(std::string &copy){body_size=copy;}
		void set_error404(std::string &copy){error404=copy;}
		void set_error418(std::string &copy){error418=copy;}
		void set_name(std::string &copy){name_server=copy;}
		void set_showdir(std::string &copy){showdir=copy;}
		void set_index(std::string &copy){index=copy;}
		void set_host(std::string &copy){host=copy;}
		void set_root(std::string &copy){root=copy;}
		void set_port(std::string &copy){port=copy;}
		std::string get_port(){return port;}
		std::string get_host(){return host;}
		std::string get_root(){return root;}
		std::string get_index(){return index;}
		std::string get_showdir(){return showdir;}
		std::string get_name(){return name_server;}
		std::string get_error418(){return error418;}
		std::string get_error404(){return error404;}
		std::string get_body_size(){return body_size;}
		std::string get_root_assets(){return root_assets;}

		void set_medallow(std::vector<std::string> copy){this->med_allow.insert(med_allow.begin(), copy.begin(), copy.end());}
		std::string get_medallow(int index){return med_allow[index];}
		size_t get_lmedallow(){return med_allow.size();}

		void set_ridirect(std::vector<std::string> copy){this->ridirect.insert(ridirect.begin(), copy.begin(), copy.end());}
		std::string get_ridirect(int index){return ridirect[index];}
		size_t get_lridirect(){return ridirect.size();}
};

class webserv{
	size_t nserv;
	public:
		std::vector<server> servers;

		void crea_server(){servers.push_back(server(*this));}
		size_t	get_n_server(){return servers.size();}
		void set_nserv(size_t serv){this->nserv=serv;}
		webserv(){nserv=0;}
		~webserv(){}
};
#endif