#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

#include <fstream>
#include "Utils.hpp"
#include "Server.hpp"

#define SUCCESS 1
#define FAILED -1
#define EMPTY -2

class ConfigParser
{
private:
	std::string content;

	Server parse_server(size_t *i);
	Location parse_location(size_t *i);

	int set_server_values(Server *server, const std::string key, const std::string value);
	int set_location_values(Location *location, const std::string key, const std::string value);

	int check_line_syntax(std::string line);
	int print_parse_error();

public:
	ConfigParser(const char* filename);
	~ConfigParser();

	std::vector<Server> *parse();
};

#endif