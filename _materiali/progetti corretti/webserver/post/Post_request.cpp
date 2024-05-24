#include "Post_request.hpp"

bool Post_request::post_allowed(Server server, std::map<std::string, std::string> request_map)
{
	std::string path; 
	//se request_map["path"] è vuoto, allora path = "/"
	if (request_map["path"] == "")
		path = "/";
	else
		path = request_map["path"];

	//se l'ultimo carattere di path è una "/" e la lunghezza di path è maggiore di 1, allora elimino l'ultimo carattere
	if (path[path.size()-1 ] == '/' && path.size() > 1)
	{
		std::string path2(path.begin(), path.end()-1);
		path = path2;
	}
	std::vector<Location> locations = server.get_locations();
	for(unsigned int i = 0; i < locations.size(); i++)
	{
		if(locations.at(i).get_path() == path)
		{
			if (locations.at(i).get_allow().GET == false && locations.at(i).get_allow().POST == false && locations.at(i).get_allow().DELETE == false)
				return true; // IMPOSTO POST DI DEFAULT A TRUE
			else
				return locations.at(i).get_allow().POST;
		}
	}
	if (server.get_allow().GET == false && server.get_allow().POST == false && server.get_allow().DELETE == false)
		return true; // IMPOSTO POST DI DEFAULT A TRUE
	return server.get_allow().POST;
}

void Post_request::post_response(int client_socket, Server server, std::map<std::string, std::string> request_map, std::vector<char> message_body, Location location)
{
	if (Post_request::post_allowed(server, request_map) == false) {
		Error_page::send_error_page(server, request_map["path"], client_socket, 405, "Method Not Allowed", location);
		return;
	}

	std::string root = Get_request::search_root(server, request_map, location);
	std::string uro = root + request_map["path"];
	request_map = Request_manager::set_file(server, request_map, location);

	std::string cgi = "";
	 
	cgi = Cgi_request::is_cgi(request_map["file"], server, request_map, location);

	if (cgi != "")
	{
		message_body.push_back('\0');
		setenv("CONTENT_LENGTH", request_map["Content-Length"].c_str(), 1);
		FILE* pipe = popen(uro.c_str(), "w");
    	if (pipe) {
        	fwrite(message_body.data(), sizeof(char), message_body.size(), pipe);
        	pclose(pipe);
			uro = root + "/cgi_response.html";
			std::ifstream in_file(uro.c_str());
			if (in_file.is_open()) 
			{
				int bytes_sent = send(client_socket, "HTTP/1.1 200 OK\r\n\r\n", 19, 0);
				if (bytes_sent == -1) {
            perror("send failed");
            return;
        }
				std::string response((std::istreambuf_iterator<char>(in_file)), std::istreambuf_iterator<char>());
				in_file.close();
				bytes_sent = send(client_socket, response.c_str(), response.size()+1, 0);
				if (bytes_sent == -1) {
            perror("send failed");
            return;
        }
			}
			else
				Error_page::send_error_page(server, request_map["path"], client_socket, 500, "Internal Server Error", location);
			return;
		}
		Error_page::send_error_page(server, request_map["path"], client_socket, 500, "Internal Server Error", location);
		return;
	}

	std::string filename = "";
	
	filename = Post_request::extract_filename(message_body);


	//se filename è vuoto, allora errore 400
	if (filename == "") {
		Error_page::send_error_page(server, request_map["path"], client_socket, 200, "DATI RICEVUTI", location);
		return;
	}

	//se filename contiene /, allora errore 400
	if (filename.find("/") != std::string::npos) {
		Error_page::send_error_page(server, request_map["path"], client_socket, 400, "Bad Request", location);
		return;
	}

	//se filename contiene spazi, sostituisco con %20

	for (size_t i = 0; i < filename.size(); i++)
	{
		if (filename[i] == ' ')
			filename.replace(i, 1, "%20");
	}

	std::string uri = root + request_map["path"] + filename;

	message_body = Post_request::extract_content(message_body);	
	std::ofstream out_file(uri.c_str(), std::ios::binary);

	if (out_file.is_open()) {
		for (size_t i = 0; i < message_body.size(); i++)
			out_file.write(&message_body.at(i), 1);
		out_file.close();
		std::string response = "HTTP/1.1 203 OK\r\n";
		response += "Server: " + server.get_server_name() + "\r\n";
		response += "Content-Type: text/html\r\n";
		response += "Connection: close\r\n";
		response += "\r\n";
		write(client_socket, response.c_str(), response.size());
		response = "<html><body><h1>File uploaded</h1><br/><a href='/'>Home</a></body></html>";
		write(client_socket, response.c_str(), response.size());
		return;
	}
	else
		Error_page::send_error_page(server, request_map["path"], client_socket, 500, "Internal Server Error", location);
}

std::string Post_request::extract_filename(std::vector<char> message_body)
{
	std::string filename;
	std::string content(message_body.begin(), message_body.end());
	//cerco filename= e prendo il nome del file
	size_t pos = content.find("filename=");
	if (pos != std::string::npos)
	{
		pos += 10;
		while (content[pos] != '"')
		{
			filename += content[pos];
			pos++;
		}
	}
	return filename;
}

std::vector<char> Post_request::extract_content(std::vector<char> message_body)
{
	std::vector<char> content;
	std::string content_string(message_body.begin(), message_body.end());
	//cerco \r\n\r\n e prendo il contenuto del file
	size_t pos = content_string.find("\r\n\r\n");
	if (pos != std::string::npos)
	{
		pos += 4;
		for (size_t i = pos; i < message_body.size(); i++)
			content.push_back(message_body.at(i));
	}

	//finche non trovo \r\n--, elimino l ultimo carattere
	while (content.size() > 4 && content.at(content.size()-4) != '\r' && content.at(content.size()-3) != '\n' && content.at(content.size()-2) != '-' && content.at(content.size()-1) != '-')
		content.pop_back();

	content.pop_back();

	//finche non trovo \n elimino l ultimo caratter

	while (content.size() > 0 && content.at(content.size()-1) != '\n')
		content.pop_back();

	content.pop_back();
	content.pop_back();

	return content;
}
