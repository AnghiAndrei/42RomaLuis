#pragma once

#include "../Webserver.hpp"
#include "../request/Request_manager.hpp"
#include "../get/Get_request.hpp"

class Post_request
{
	public:
		Post_request(){};
		~Post_request(){};

		static void post_response(int client_socket, Server server, std::map<std::string, std::string> request_map, std::vector<char> message_body, Location location);
		static bool post_allowed(Server server, std::map<std::string, std::string> request_map);
		static std::string extract_filename(std::vector<char> message_body);
		static std::vector<char> extract_content(std::vector<char> message_body);
};