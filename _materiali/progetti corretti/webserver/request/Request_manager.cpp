#include "Request_manager.hpp"

std::map<std::string, std::string> Request_manager::parse_request(std::string file){
	
	std::map<std::string, std::string> request_map;
	std::string line;
	std::istringstream file_stream(file);

	std::vector<std::string> request_and_params = Utilities::split(file, "\n", 1);
	std::vector<std::string> request = Utilities::split(request_and_params.at(0), " ", 1);
	if (request.size() != 3)
	{
		request_map["error"] = "400";
		return request_map;
	}
	request_map["request"] = request.at(0);
	request_map["path"] = request.at(1);
	request_map["http_version"] = request.at(2);

	while (std::getline(file_stream, line))
	{
		std::string key;
		std::string value;
		std::istringstream line_stream(line);
		std::getline(line_stream, key, ':');
		std::getline(line_stream, value);
		Utilities::trim(key);
		Utilities::trim(value);
		request_map[key] = value;
	}

	std::string hostname = request_map["Host"];
	std::vector<std::string> host = Utilities::split(hostname, ":", 1);
	if (host.size() == 2)
	{
		request_map["host"] = Utilities::trim(host.at(0));
		request_map["port"] = Utilities::trim(host.at(1));
	}
	else
	{
		request_map["host"] = Utilities::trim(host.at(0));
		request_map["port"] = "80";
	}

	if (request_map["path"] == "")
		request_map["path"] = "/";
	
	if (request_map["path"][request_map["path"].size()-1 ] == '/' && request_map["path"].size() > 1)
		{
			std::string path(request_map["path"].begin(), request_map["path"].end()-1);
			request_map["path"] = path;
		}

	request_map["file"] = "";

	return request_map;
}

std::vector<char> Request_manager::recive_request(int client_socket)
{
	std::vector<char> httpRequest;
    const int bufferSize = 1;
    
    char buffer[bufferSize];
    int bytesRead;
    
	while (1)
	{
		bytesRead = read(client_socket, buffer, bufferSize);
		httpRequest.insert(httpRequest.end(), buffer, buffer + bytesRead);
		if (httpRequest.size() > 4 && httpRequest.at(httpRequest.size()-4) == '\r' && httpRequest.at(httpRequest.size()-3) == '\n' && httpRequest.at(httpRequest.size()-2) == '\r' && httpRequest.at(httpRequest.size()-1) == '\n')
			break;
	}

    return httpRequest;
}

std::vector<char> Request_manager::get_request_body(int client_socket, size_t n)
{
	std::vector<char> message_body;
	const int bufferSize = 1;
	char buffer[bufferSize];
	int bytesRead;

	size_t i = 0;

	while (i < n)
	{
		bytesRead = read(client_socket, buffer, bufferSize);
		if (bytesRead != 0)
			message_body.insert(message_body.end(), buffer, buffer + bytesRead);
		i++;
	}
/*
	message_body.pop_back();

	while (message_body.size() > 0 && message_body.at(message_body.size()-1) != '\n')
		message_body.pop_back();

	message_body.pop_back();
*/
	return message_body;
}

std::map<std::string, std::string> Request_manager::set_file(Server server, std::map<std::string, std::string> request_map, Location location)
{
	std::string root = Get_request::search_root(server, request_map, location);

	std::string uri = root + request_map["path"];

	struct stat st;

	request_map["file"] = "";

	if(stat(uri.c_str(), &st) == 0)
	{
		if((st.st_mode & S_IFMT) == S_IFDIR)
		{
			if (uri[uri.size()-1] != '/')
				request_map["path"] += "/";
			return request_map;
		}
		else
		{
			std::vector<std::string> file = Utilities::split(uri, "/", 1);
			request_map["file"] = file.at(file.size()-1);
			std::string path(request_map["path"].begin(), request_map["path"].end()-request_map["file"].size());
			request_map["path"] = path;
			return request_map;
		}
	}
/*	std::vector<std::string> file = Utilities::split(uri, "/", 1);
			request_map["file"] = file.at(file.size()-1);
			std::string path(request_map["path"].begin(), request_map["path"].end()-request_map["file"].size());
			request_map["path"] = path;
			return request_map;*/

	return request_map;
}

int Request_manager::search_max_body_size(Server server, std::map<std::string, std::string> request_map, Location location)
{
	(void)request_map;
	if (location.get_client_max_body_size() != 0)
		return server.get_client_max_body_size();
	return server.get_client_max_body_size();
}


Location Request_manager::select_location(Server server, std::string path)
{
	std::vector<Location> locations = server.get_locations();
	std::string longest_path = "";
	Location location;
	for (std::vector<Location>::iterator it = locations.begin(); it != locations.end(); it++)
	{
		if (path.find(it->get_path()) == 0 && it->get_path().size() > longest_path.size())
		{
			longest_path = it->get_path();
			location = *it;
		}
	}
	return location;
}