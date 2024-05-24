#pragma once

#include <string>
#include <vector>
#include <map>
#include <sstream>
#include "../utilities/Utilities.hpp"
#include "../Webserver.hpp"

class Request_manager
{
	public:
			struct Request
			{
				std::string message;
				std::vector<char> message_body;
				std::map<std::string, std::string> request_map;
			};

			Request_manager(){};
			~Request_manager(){};
			
			static std::vector<char> recive_request(int client_socket);
			static std::map<std::string, std::string> parse_request(std::string request);
			static std::vector<char> get_request_body(int client_socket, size_t content_length);
			static std::map<std::string, std::string> set_file(Server server, std::map<std::string, std::string> request_map, Location location);
			static int search_max_body_size(Server server, std::map<std::string, std::string> request_map, Location location);
			static Location select_location(Server server, std::string path);
};