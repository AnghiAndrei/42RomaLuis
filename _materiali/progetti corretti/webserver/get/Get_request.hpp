#pragma once

#include "../Webserver.hpp"
#include "AutoIndex.hpp"
#include "Cgi_request.hpp"

class Get_request
{
	public:
		Get_request(){};
		~Get_request(){};

		static void get_response(int client_socket, Server server, std::map<std::string, std::string> request_map, Location location);
		static bool get_allowed(Server server, std::map<std::string, std::string> request_map, Location location);
		static void get_response_directory(int client_socket, Server server, std::map<std::string, std::string> request_map, std::string root, Location location);
		static std::string search_index(Server server, std::map<std::string, std::string> request_map, Location location);
		static std::string search_root(Server server, std::map<std::string, std::string> request_map, Location location);
		static std::string search_rewrite(Server server, std::map<std::string, std::string> request_map, Location location);
};	