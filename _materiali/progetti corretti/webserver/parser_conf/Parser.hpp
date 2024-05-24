#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

#include "../server/Server.hpp"


class Parser {

public:
	Parser(){};
	~Parser(){};

	static std::vector<Server> config(const char *file);

private:
	static std::vector<std::string> open_file(const char *file);
	static std::vector<std::string> tokenize_conf(std::string line);
	static std::vector<std::vector<std::string> > parse_server(std::vector<std::string> tokens);
	static Server config_server(std::vector<std::string> tokens);
	static void check_semicolon(std::vector<std::string>::iterator &it);
	static Location config_location(std::vector<std::string>::iterator it);
};