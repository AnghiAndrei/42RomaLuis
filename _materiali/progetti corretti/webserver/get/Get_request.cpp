#include "Get_request.hpp"

void sendFile(int client_sock, std::vector<char> fileContent, std::string file)
{
	(void)file;
	std::stringstream ss;
	ss << fileContent.size();	
	std::string content_length = ss.str();
	std::string header = "HTTP/1.1 200 OK\r\n";
	header += "Content-Type: application/octet-stream\r\n";
	header += "Cache-Control: no-store, must-revalidate\r\n";
	header += "Pragma: no-cache\r\n";
	header += "Content-Length: "+ content_length + "\r\n";
	header += "\r\n";
	int bytes_sent = write(client_sock, header.c_str(), header.size());
	if (bytes_sent == -1) {
            perror("send failed");
            return;
        }
	bytes_sent = write(client_sock, fileContent.data(), fileContent.size());

	if (bytes_sent == -1) {
            perror("send failed");
            return;
        }
}

void sendpage(int client_sock, std::string fileContent, std::string file)
{
	(void)file;
	std::stringstream ss;
	ss << fileContent.size();
	std::string content_length_byte = ss.str();

	std::string header = "HTTP/1.1 200 OK\r\n";
	header += "Content-Type: text/html\r\n";
	header += "Cache-Control: no-store, must-revalidate\r\n";
	header += "Pragma: no-cache\r\n";
	header += "Content-Length: " + content_length_byte + "\r\n";
	header += "\r\n";
	header += fileContent;
	int bytes_sent = write(client_sock, header.c_str(), header.size()+1);
	if (bytes_sent == -1) {
            perror("send failed");
            return;
        }
}

void sendFile2(int client_sock, std::ifstream &in_file)
{
	std::string fileContent((std::istreambuf_iterator<char>(in_file)), std::istreambuf_iterator<char>());
	int bytes_sent = write(client_sock, fileContent.c_str(), fileContent.size());
	if (bytes_sent == -1) {
            perror("send failed");
            return;
        }
}


bool Get_request::get_allowed(Server server, std::map<std::string, std::string> request_map, Location location)
{
	(void)request_map;
	if (location.get_root() != "")
	{
		if (location.get_allow().DELETE == false && location.get_allow().GET == false && location.get_allow().POST == false)
		{
			return server.get_allow().GET; //DEFAULT SE ESISTE LOCATION MA NON HA ALLOW
		}	
		return location.get_allow().GET;
	}
	else
	{
		return server.get_allow().GET; //DEFAULT PRENDE SERVER
	}
}

void Get_request::get_response(int client_sock, Server server, std::map<std::string, std::string> request_map, Location location)
{

	if (request_map["path"].find("http://") == 0 || request_map["path"].find("https://") == 0)
	{
		std::string header2 = "<html><head><title>Redirecting...</title></head><body>";
		header2 += "Redirecting to <a href=\""+request_map["path"]+"\">nuovo-url</a>.";
		header2 += "</body></html>";
		std::stringstream ss;
		ss << header2.size();
		std::string content_length = ss.str();
		std::string header = "HTTP/1.1 302 Found\r\n";
		header += "Location: "+request_map["path"]+"\r\n";
		header += "Content-type: text/html\r\n";
		header += "Content-Length: "+content_length+"\r\n";
		header += "\r\n";
		int bytes_sent = send(client_sock, header.c_str(), header.size()+1, 0);
		if (bytes_sent == -1) {
            perror("send failed");
            return;
        }
		return;
	}
	
	std::string root = Get_request::search_root(server, request_map, location);

	if (Get_request::get_allowed(server, request_map, location) == false) {
		Error_page::send_error_page(server, request_map["path"], client_sock, 405, "Method Not Allowed", location);
		return;
	}

	std::string uri = root + request_map["path"];

	std::string rewrite = Get_request::search_rewrite(server, request_map, location);
	if (rewrite != "")
	{
		request_map["path"] = rewrite;
		Get_request::get_response(client_sock, server, request_map, location);
		return;
	}

	request_map = Request_manager::set_file(server, request_map, location);

	std::string cgi = "";

	rewrite = Get_request::search_rewrite(server, request_map, location);
	if (rewrite != "")
	{
		request_map["path"] = rewrite;
		Get_request::get_response(client_sock, server, request_map, location);
		return;
	}
	
	if (request_map["file"] == "") {
		Get_request::get_response_directory(client_sock, server, request_map, root, location);
		return;
	}

	
	cgi = Cgi_request::is_cgi(request_map["file"], server, request_map, location);
	//se cgi non è vuoto allora eseguo e il file esiste lo eseguo                
	if (cgi != "")
	{
		//verifico che il file esista
		std::string uri_cgi = root + request_map["path"] + request_map["file"];
		struct stat st;
		if(stat(uri_cgi.c_str(), &st) == 0)
		{
			Cgi_request::cgi_response(client_sock, server, request_map, cgi, uri, location);
			Cgi_request::result(client_sock);
			return;
		}
		else
		{
			Error_page::send_error_page(server, request_map["path"], client_sock, 404, "Not Found", location);
			return;
		}
	}

	bool is_html = false;

	std::string file_extension = request_map["file"].substr(request_map["file"].find_last_of(".") + 1);

	if (file_extension == "html" || file_extension == "htm")
		is_html = true;

	if (is_html == true)  //IS HTML
	{
		std::ifstream in_file(uri.c_str(), std::ios::binary);
		if (in_file.is_open()) 
		{
			std::string fileContent((std::istreambuf_iterator<char>(in_file)), std::istreambuf_iterator<char>());
			sendpage(client_sock, fileContent, request_map["file"]);
			in_file.close();
			return;
		}

	}
	else //IS A FILE
	{
		std::ifstream in_file(uri.c_str(), std::ios::binary);
		if (in_file.is_open()) 
		{
			std::vector<char> buffer((std::istreambuf_iterator<char>(in_file)), std::istreambuf_iterator<char>());
			sendFile(client_sock, buffer, request_map["file"]);
			in_file.close();
			return;
		}
	}
	Error_page::send_error_page(server, request_map["path"], client_sock, 404, "Not Found", location);
}

void Get_request::get_response_directory(int client_sock, Server server, std::map<std::string, std::string> request_map, std::string root, Location location)
{

	request_map["file"] = Get_request::search_index(server, request_map, location);
	std::string uri;

	if (request_map["path"] == "/")
		uri = root + request_map["path"] + request_map["file"];
	else
		uri = root + request_map["path"] +"/"+ request_map["file"];

	struct stat st;

	if(stat(uri.c_str(), &st) == 0)
	{
		std::ifstream in_file(uri.c_str());
		if (in_file.is_open()) 
		{
			std::string fileContent((std::istreambuf_iterator<char>(in_file)), std::istreambuf_iterator<char>());
			sendpage(client_sock, fileContent, request_map["file"]);
			in_file.close();
			return;
		}
	}

	if (request_map["path"][request_map["path"].size()-1 ] == '/' && request_map["path"].size() > 1)
	{
		std::string path(request_map["path"].begin(), request_map["path"].end()-1);
		request_map["path"] = path;
	}
	
	if (location.get_autoindex() == true)
	{
		std::string response_body = AutoIndex::createAutoIndex(server, request_map["path"], root);
		sendpage(client_sock, response_body, request_map["file"]);
		return;
	}

	if (location.get_path() != "" && location.get_autoindex() == false)
	{
		Error_page::send_error_page(server, request_map["path"], client_sock, 403, "Forbidden", location);
		return;
	}

	if (server.get_autoindex() == true)
	{
		std::string response_body = AutoIndex::createAutoIndex(server, request_map["path"], root);
		sendpage(client_sock, response_body, request_map["file"]);
		return;
	}

	Error_page::send_error_page(server, request_map["path"], client_sock, 404, "Not Found", location);

}

std::string Get_request::search_index(Server server, std::map<std::string, std::string> request_map, Location location)
{
	(void)request_map;
	if (location.get_index() != "")
		return location.get_index();
	return server.get_index();
}

std::string Get_request::search_root(Server server, std::map<std::string, std::string> request_map, Location location)
{
	(void)request_map;
	if (location.get_root() != "")
		return location.get_root();
	return server.get_root();
}

std::string Get_request::search_rewrite(Server server, std::map<std::string, std::string> request_map, Location location)
{
	std::string res = "";
	
	std::vector<rewrite> rewrite = location.get_rewrite();
	for(unsigned int j = 0; j < rewrite.size(); j++)
	{
		if (rewrite.at(j).from == request_map["path"]+request_map["file"])
			res = rewrite.at(j).to;
	}
		
	if (res != "")
		return res;
	
	for (size_t i = 0; i < server.get_rewrite().size(); i++)
	{
		if (server.get_rewrite().at(i).from == request_map["path"]+request_map["file"])
			res = server.get_rewrite().at(i).to;
	}
	return res;
}

