#pragma once

#include "../Webserver.hpp"
#include "../cgi/Cgi.hpp"

class Cgi_request
{	
	public:
		Cgi_request(){};
		~Cgi_request(){};

		static std::string is_cgi(std::string file, Server server, std::map<std::string, std::string> request_map, Location location);
		static void cgi_response(int client_sock, Server server, std::map<std::string, std::string> request_map, std::string root_cgi, std::string root, Location location);
		static void result(int client_sock);

};