#include "../includes/ServerManager.hpp"

void ServerManager::print_servers_info()
{
	std::cout << "=================================================\n";
	std::cout << "            Total Server Informations            \n";
	std::cout << "=================================================\n";
	std::map<std::string, Server*>::iterator it;
	for (it = default_servers.begin(); it != default_servers.end(); it++)
		(*it).second->print_server_info();
	std::cout << "=================================================\n";
}

bool	ServerManager::is_allowed_method(std::vector<MethodType> allow_methods, std::string method) 
{
	if (method == "GET")
		return true;
	for (std::vector<MethodType>::iterator it = allow_methods.begin(); 
	it != allow_methods.end(); it++)
	{
		if (method == methodtype_to_s(*it))
			return true;
	}
	return false;
}

bool	ServerManager::is_loc_check(std::string path, Client &client)
{
	Location *cur_loc = client.server->get_cur_location(path);
	if (!cur_loc)
		return false;
	std::string root = cur_loc->path;
	if (path == root)
		return true;
	return false;
}

bool	ServerManager::is_request_done(char *request)
{
	char *body = strstr(request, "\r\n\r\n");
	if (!body)
		return false;
	body += 4;
	if (strnstr(request, "chunked", strlen(request) - strlen(body)))
	{
		if (strstr(body, "\r\n\r\n"))
			return true;
		return false;
	}
	else if (strnstr(request, "Content-Length", strlen(request) - strlen(body)))
	{
		if (strstr(body, "\r\n\r\n"))
			return true;
		char *start = strnstr(request, "Content-Length: ", strlen(request) - strlen(body)) + 16;
		char *end = strstr(start, "\r\n");
		char *len = strndup(start, end - start);
		free(len);
		int len_i = atoi(len);
		if ((size_t)len_i <= strlen(body))
			return true;
		return false;
	}
	else if (strnstr(request, "boundary=", strlen(request) - strlen(body)))
	{
		if (strstr(body, "\r\n\r\n"))
			return true;
		return false;
	}
	return true;
}

bool ServerManager::is_response_timeout(Client& client)
{
	static timeval tv;
	
	gettimeofday(&tv, NULL);
	if (tv.tv_sec - client.get_last_time().tv_sec > client.server->recv_timeout.tv_sec) return true;
	client.set_last_time_sec(tv);
	return false;
}

bool	ServerManager::is_cgi(Request *request, Location *loc)
{
	for (std::map<std::string, std::string>::iterator it = loc->cgi_info.begin();
	it != loc->cgi_info.end(); it++)
	{
		std::cout << "get_path: " << request->get_path() << "\n";
		std::cout << "it->first: " << it->first << "\n"; 
		if (request->get_path().find(it->first) != std::string::npos)
			return true;
	}
	return false;
}

std::string ServerManager::methodtype_to_s(MethodType method)
{
	if (method == GET)
		return "GET";
	else if (method == POST)
		return "POST";
	else if (method == DELETE)
		return "DELETE";
	return "";
}

const char *ServerManager::find_content_type(const char *path)
{
	const char *last_dot = strrchr(path, '.');
	if (last_dot)
	{
		if (strcmp(last_dot, ".css") == 0) return "text/css";
		if (strcmp(last_dot, ".csv") == 0) return "text/csv";
		if (strcmp(last_dot, ".html") == 0) return "text/html";
		if (strcmp(last_dot, ".js") == 0) return "application/javascript";
		if (strcmp(last_dot, ".json") == 0) return "application/json";
		if (strcmp(last_dot, ".pdf") == 0) return "application/pdf";
		if (strcmp(last_dot, ".gif") == 0) return "image/gif";
		if (strcmp(last_dot, ".jpeg") == 0) return "image/jpeg";
		if (strcmp(last_dot, ".jpg") == 0) return "image/jpeg";
		if (strcmp(last_dot, ".png") == 0) return "image/png";
		if (strcmp(last_dot, ".svg") == 0) return "image/svg+xml";
	}
	return "text/plain";
}

std::string ServerManager::find_path_in_root(std::string path, Client &client)
{
	std::string full_path = "";
	std::string location;
	full_path.append(client.get_root_path(path));
	Location *loc = client.server->get_cur_location(path);
	if (loc)
		location = loc->path;
	else
		location = "";
	std::string str = path.substr(location.length());
	full_path.append(str);
	return full_path;
}

std::string ServerManager::get_status_cgi(std::string& cgi_ret)
{
	std::string status_line;
	std::stringstream ss(cgi_ret);

	std::string line;
	while (getline(ss, line, '\n'))
	{
		if (line.substr(0, 6) == "Status")
			status_line = line;
	}
	if (status_line.empty())
		return status_line;
	cgi_ret.erase(0, status_line.length() + 1);
	status_line.erase(0, 8);
	status_line.erase(status_line.length() - 1, 1);
	return status_line;
}

void	ServerManager::write_file_in_path(Client &client, std::string content, std::string path)
{
	std::cout << "> write in: " << path << "\n";
	size_t index = path.find_last_of("/");
	std::string file_name = path.substr(index + 1);
	std::string folder_path = path.substr(0, index);

	std::string command = "mkdir -p " + folder_path;
	system(command.c_str());
	FILE *fp = fopen(path.c_str(), "w");
	if (!fp)
	{
		send_error_page(500, client);
		return;
	}

	fwrite(content.c_str(), content.size(), 1, fp);
	fclose(fp);
}