#include "Parser.hpp"
	#include <fstream>

std::vector<std::string> Parser::open_file(const char *file)
{
	std::vector<std::string> tokens;
	try
	{
		std::ifstream conf_file(file);
		std::string line;

		if (conf_file.is_open())
		{
			while (getline(conf_file, line))
			{
				std::vector<std::string> token_line;
				token_line = tokenize_conf(line);
				std::copy(token_line.begin(), token_line.end(), std::back_inserter(tokens));
			}
			conf_file.close();
		}
		else
		{
			throw (std::runtime_error("Error: Unable to open file"));
		}
	}
	catch (std::runtime_error &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return tokens;
}
	
std::vector<std::string> Parser::tokenize_conf(std::string line)
{
	std::vector<std::string> tokens;
	for (unsigned int i = 0; i < line.size(); i++)
	{
		std::string temp = "";
		while((line[i] == ' ' || line[i] == '\t') && i < line.size() && line[i] != '\0')
			i++;
		if (line[i] == '#' || line[i] == '\0')
			break;
		if (line[i] == '{' || line[i] == '}' || line[i] == ';')
		{
			temp += line[i];
			tokens.push_back(temp);
			temp = "";
			continue;
		}
		while(line[i] != ' ' && i < line.size() && line[i] != '\t' && line[i] != '\r' && line[i] != ';' && line[i] != '{' && line[i] != '}' && line[i] != '\0' && line[i] != '\n' && line[i] != '#')
		{
			temp += line[i];
			i++;
		}
		i--;
		tokens.push_back(temp);
		if (line[i] == '#')
			break;
	}
	return tokens;
}

std::vector<Server> Parser::config(const char *file)
{
	std::vector<Server> servers;
	std::vector<std::vector<std::string> > server_tokens = parse_server(open_file(file));
	for (std::vector<std::vector<std::string> >::iterator it = server_tokens.begin(); it != server_tokens.end(); it++)
	{
		Server server = config_server(*it);
		servers.push_back(server);
	}
	return servers;
}

void Parser::check_semicolon(std::vector<std::string>::iterator &it)
{
	if (*(it+1) != ";")
	{
		std::cerr << "Error: Syntax Error" << std::endl;
		exit (1);
	}
	it += 2;
}

Location Parser::config_location(std::vector<std::string>::iterator it)
{
	Location location = Location();
	if (*it != "location")
	{
		std::cerr << "Error: location block" << std::endl;
		return location;
	}
	location.set_path(*(it+1));
	it++;
	if (*(it+1) != "{")
	{
		std::cerr << "Error: location block" << std::endl;
		return location;
	}
	it += 2;
	while (*it != "}")
	{
		if (*it == ";")
		{
			std::cerr << "Error: Syntax Error" << std::endl;
			exit (1);
		}
		if (*it == "root")
		{
			location.set_root(*(it+1));
			it++;
			check_semicolon(it);
			continue;
		}
		if (*it == "upload")
		{
			location.set_upload(*(it+1));
			it++;
			check_semicolon(it);
			continue;
		}
		if (*it == "cgi")
		{
			std::vector<CGI> cgi_vec = location.get_cgi();
			CGI cgi;
			it++;
			cgi.name = *it;
			it++;
			cgi.path = *it;
			cgi_vec.push_back(cgi);
			location.set_cgi(cgi_vec);
			check_semicolon(it);
			continue;
		}
		if (*it == "client_max_body_size")
		{
			location.set_client_max_body_size(atoi((it+1)->c_str()));
			it++;
			check_semicolon(it);
			continue;
		}
		if (*it == "allow_methods")
		{
			it++;
			allow_methods allow;
			allow.GET = false;
			allow.POST = false;
			allow.DELETE = false;
			while (*it != ";" && *it != "}")
			{
				if (*it == "GET")
					allow.GET = true;
				if (*it == "POST")
					allow.POST = true;
				if (*it == "DELETE")
					allow.DELETE = true;
				it++;
			}
			location.set_allow(allow);
			it--;
			check_semicolon(it);
			continue;
		}
		if (*it == "index")
		{
			location.set_index(*(it+1));
			it++;
			check_semicolon(it);
			continue;
		}
		if (*it == "rewrite")
		{
			std::vector<rew> rewrite_vec = location.get_rewrite();
			rew rewrite;
			it++;
			rewrite.from = *it;
			it++;
			rewrite.to = *it;
			it++;
			rewrite.type = *it;
			rewrite_vec.push_back(rewrite);
			location.set_rewrite(rewrite_vec);
			check_semicolon(it);
			continue;
		}
		if (*it == "error_page")
		{
			std::vector<error_pages> error_page_vec = location.get_error_page();
			error_pages error_page;
			it++;
			error_page.code = atoi(it->c_str());
			it++;
			error_page.path = *it;
			error_page_vec.push_back(error_page);
			location.set_error_page(error_page_vec);
			check_semicolon(it);
			continue;
		}
			if (*it == "autoindex")
		{
			if (*(it+1) == "on")
				location.set_autoindex(true);
			else if (*(it+1) == "off")
				location.set_autoindex(false);
			else
			{
				std::cerr << "Error: Invalid autoindex value" << std::endl;
				exit (1);
			}
			it++;
			check_semicolon(it);
			continue;
		}
		if (*it == "}")
		{
			std::cout << "Location block ended" << std::endl;
			it++;
		}
		else
		{
			std::cout << *it << std::endl;
			std::cerr << "Error: Invalid token" << std::endl;
			exit (1);
		}
	}
	it++;
	return location;
}

Server Parser::config_server(std::vector<std::string> tokens)
{
	Server server;
	std::vector<std::string>::iterator it = tokens.begin();
	if (*it != "server")
	{
		std::cerr << "Error: server block" << std::endl;
		exit (1);
	}
	if (*(it+1) != "{")
	{
		std::cerr << "Error: server block" << std::endl;
		exit (1);
	}
	it += 2;
	while (it != tokens.end())
	{
		if (*it == ";")
		{
			std::cerr << "Error: Syntax Error" << std::endl;
			exit (1);
		}
		if (*it == "server_name")
		{
			server.set_server_name(*(it+1));
			it++;
			check_semicolon(it);
			continue;
		}
		if (*it == "listen")
		{
			server.set_listen(atoi((it+1)->c_str()));
			it++;
			check_semicolon(it);
			continue;
		}
		if (*it == "root")
		{
			server.set_root(*(it+1));
			it++;
			check_semicolon(it);
			continue;
		}
		if (*it == "upload")
		{
			server.set_upload(*(it+1));
			it++;
			check_semicolon(it);
			continue;
		}
		if (*it == "cgi")
		{
			std::vector<CGI> cgi_vec = server.get_cgi();
			CGI cgi;
			it++;
			cgi.name = *it;
			it++;
			cgi.path = *it;
			cgi_vec.push_back(cgi);
			server.set_cgi(cgi_vec);
			check_semicolon(it);
			continue;
		}
		if (*it == "client_max_body_size")
		{
			server.set_client_max_body_size(atoi((it+1)->c_str()));
			it++;
			check_semicolon(it);
			continue;
		}
		if (*it == "allow_methods")
		{
			it++;
			allow_methods allow;
			allow.GET = false;
			allow.POST = false;
			allow.DELETE = false;
			while (*it != ";" && it != tokens.end())
			{
				if (*it == "GET")
					allow.GET = true;
				if (*it == "POST")
					allow.POST = true;
				if (*it == "DELETE")
					allow.DELETE = true;
				it++;
			}
			server.set_allow(allow);
			it--;
			check_semicolon(it);
			continue;
		}
		if (*it == "index")
		{
			server.set_index(*(it+1));
			it++;
			check_semicolon(it);
			continue;
		}
		if (*it == "rewrite")
		{
			std::vector<rew> rewrite_vec = server.get_rewrite();
			rew rewrite;
			it++;
			rewrite.from = *it;
			it++;
			rewrite.to = *it;
			it++;
			rewrite.type = *it;
			rewrite_vec.push_back(rewrite);
			server.set_rewrite(rewrite_vec);
			check_semicolon(it);
			continue;
		}
		if (*it == "error_page")
		{
			std::vector<error_pages> error_page_vec = server.get_error_page();
			error_pages error_page;
			it++;
			error_page.code = atoi(it->c_str());
			it++;
			error_page.path = *it;
			error_page_vec.push_back(error_page);
			server.set_error_page(error_page_vec);
			check_semicolon(it);
			continue;
		}
		if (*it == "autoindex")
		{
			if (*(it+1) == "on")
				server.set_autoindex(true);
			else if (*(it+1) == "off")
				server.set_autoindex(false);
			else
			{
				std::cerr << "Error: Invalid autoindex value" << std::endl;
				exit (1);
			}
			it++;
			check_semicolon(it);
			continue;
		}
		if (*it == "cgi-bin")
		{
			server.set_cgi_bin(*(it+1));
			it++;
			check_semicolon(it);
			continue;
		}
		if (*it == "location")
		{
			std::vector<Location> locations = server.get_locations();
			Location location = config_location(it);
			locations.push_back(location);
			server.set_locations(locations);
			while (*it != "}")
				it++;
			continue;
		}
		if (*it == "}")
		{
			it++;
		}
		else
		{
			std::cerr << "Error: Invalid token" << std::endl;
			exit (1);
		}
	}
	
	return server;
}

std::vector<std::vector<std::string> >  Parser::parse_server(std::vector<std::string> tokens)
{
	std::vector<std::vector<std::string> > servers;
	std::vector<std::string>::iterator it = tokens.begin();
	std::vector<std::string> server;
	int bracket_count = 0;

	while (it != tokens.end())
	{
		if (*it == "{")
			bracket_count++;
		if (*it == "}")
			bracket_count--;
		server.push_back(*it);
		if (bracket_count == 0 && server.size() > 1)
		{
			servers.push_back(server);
			server.clear();
			bracket_count = 0;
		}
		it++;
	}
	if (bracket_count != 0 || server.size() != 0)
	{
		std::cerr << "Error: Syntax Error" << std::endl;
		exit (1);
	}
	return servers;	
}