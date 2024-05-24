#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <sstream>

#include "../server/Server.hpp"
#include "../server/Location.hpp"
#include "../utilities/Utilities.hpp"
#include "../Webserver.hpp"

class Error_page
{
	public:
		Error_page(){};
		~Error_page(){};
		static void send_error_page(Server server, std::string uri, int client_sock, int error_code, std::string text, Location location);
		static std::string search_error_page(std::vector<error_pages> error_page, int error_code);
		static void sendpage(int client_sock, std::string fileContent, std::string file);
};