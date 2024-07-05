#include "../includes/Location.hpp"

Location::Location(/* args */)
{
	path = "";
	root = "";
}

Location::~Location()
{
}

void Location::print_location_info()
{
	std::cout << "----------------- Location Info -----------------\n";
	std::cout << "> path: " << path << "\n";
	std::cout << "> root: " << root << "\n";
	std::cout << "> index: " << index << "\n";
	std::cout << "> allow_methods: " << allow_methods << "\n";
	for (std::map<std::string, std::string>::iterator i = cgi_info.begin(); i != cgi_info.end(); i++)
	{
		std::cout << "> cgi_info: " << (*i).first << ", " << (*i).second << "\n";
	}
}

MethodType Location::s_to_methodtype(std::string str)
{
	if (str == "GET")
	{
		return GET;
	}
	else if (str == "POST")
	{
		return POST;
	}
	else if (str == "DELETE")
	{
		return DELETE;
	}
	return INVALID;
}

std::string Location::getCgiBinary(std::string &extension)
{
	for (std::map<std::string, std::string>::const_iterator it = this->cgi_info.begin();
	it != this->cgi_info.end(); ++it)
	{
		if (it->first == "." + extension)
			return it->second;
	}
	return "";
}

std::string Location::get_root(void)
{
	return this->root;
}

std::string Location::get_path(void)
{
	return this->path;
}
