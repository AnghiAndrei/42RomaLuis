#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "DataStructs.hpp"
#include "Utils.hpp"

class Location
{
public:
	int client_body_limit;
	std::string path;
	std::string root;
	std::vector<std::string> index;
	std::vector<MethodType> allow_methods;
	std::map<std::string, std::string> cgi_info;

public:
	Location();
	~Location();

	void print_location_info();
	std::string get_root();
	std::string get_path();
	static MethodType s_to_methodtype(std::string str);
	std::string getCgiBinary(std::string &extension);
};

#endif