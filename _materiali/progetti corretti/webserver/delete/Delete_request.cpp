#include "Delete_request.hpp"

void Delete_request::delete_response(int client_socket, Server server, std::map<std::string, std::string> request_map, Location location)
{

	if (Delete_request::delete_allowed(server, request_map, location) == false)
	{
		Error_page::send_error_page(server, request_map["path"], client_socket, 403, "Forbidden", location);
		return;
	}

	std::string root = Delete_request::search_root(server, request_map, location);

	struct stat sb;
	
	std::string path = root + request_map["path"];
	
	if (stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		std::string directoryPath = root + request_map["path"];

		std::string command = "rm -rf " + directoryPath;

		int result = std::system(command.c_str());

		if (result == 0) {
			std::string response = "HTTP/1.1 200 OK\r\n\r\n";
			int bytes_sent = send(client_socket, response.c_str(), response.size(), 0);
			if (bytes_sent == -1) {
            perror("send failed");
            return;
        }
			return;
		} else {
			Error_page::send_error_page(server, request_map["path"], client_socket, 500, "Internal Server Error", location);
			return;
		}
	}
	else
	{
		request_map = Request_manager::set_file(server, request_map, location);

		std::string path = root + request_map["path"]+request_map["file"];
		
		if (remove(path.c_str()) == 0)
		{
			std::string response = "HTTP/1.1 200 OK\r\n\r\n";
			int bytes_sent = send(client_socket, response.c_str(), response.size(), 0);
			if (bytes_sent == -1) {
            perror("send failed");
            return;
        }
		}	
		else
		{
			Error_page::send_error_page(server, request_map["path"], client_socket, 500, "Internal Server Error", location);
		}
	}
}

std::string Delete_request::search_root(Server server, std::map<std::string, std::string> request_map, Location location)
{
	(void)request_map;
	if (location.get_root() != "")
		return location.get_root();
	return server.get_root();
}

bool Delete_request::delete_allowed(Server server, std::map<std::string, std::string> request_map, Location location)
{
	(void)request_map;
	if (location.get_root() != "")
	{
		if (location.get_allow().DELETE == false && location.get_allow().GET == false && location.get_allow().POST == false)
		{
			return server.get_allow().DELETE; //DEFAULT SE ESISTE LOCATION MA NON HA ALLOW
		}	
		return location.get_allow().DELETE;
	}
	else
	{
		return server.get_allow().DELETE; //DEFAULT PRENDE SERVER
	}
}