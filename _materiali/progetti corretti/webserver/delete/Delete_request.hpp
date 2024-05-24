#pragma once

#include "../Webserver.hpp"
#include "../request/Request_manager.hpp"
#include <cstdlib>

class Delete_request
{
	public:
		Delete_request(){};
		~Delete_request(){};

		static void delete_response(int client_socket, Server server, std::map<std::string, std::string> request_map, Location location);
		static bool delete_allowed(Server server, std::map<std::string, std::string> request_map, Location location);
		static std::string search_root(Server server, std::map<std::string, std::string> request_map, Location location);
};