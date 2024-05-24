#include "Cgi_request.hpp"

void sendCgi(int client_sock, std::string fileContent, std::string file)
{
	(void)file;
	std::stringstream ss;
	ss << fileContent.size();
	std::string content_length = ss.str();
	std::string header = "HTTP/1.1 200 OK\r\n";
	header += "Content-Type: application/octet-stream\r\n";
	header += "Content-Length: " + content_length + "\r\n";
	header += "\r\n";
	header += fileContent;
	header += "\r\n";
	int bytes_sent = write(client_sock, header.c_str(), header.size()+1);
	if (bytes_sent == -1) {
            perror("send failed");
            return;
        }
}


std::string Cgi_request::is_cgi(std::string file, Server server, std::map<std::string, std::string> request_map, Location location)
{
	if (request_map["file"] == "")
		return "";

	std::string file_extension = file.substr(request_map["file"].find_last_of("."));

	if (file_extension == "" || file_extension == "/" || file_extension == ".html" || file_extension == ".htm")
		return "";

	std::vector<CGI> cgi = location.get_cgi();
	for (size_t j = 0; j < cgi.size(); j++)
	{
		if (file_extension == cgi[j].path)
			return cgi[j].name;
	}
	cgi = server.get_cgi();
	for (size_t i = 0; i < cgi.size(); i++)
	{

		if (file_extension == cgi[i].path)
			return cgi[i].name;
	}
	return "";
}

void Cgi_request::cgi_response(int client_sock, Server server, std::map<std::string, std::string> request_map, std::string root_cgi, std::string uri, Location location)
{
	(void)root_cgi;
	std::ifstream in_file(uri.c_str());
	
	if (in_file.is_open()) {
		Cgi cgi;
		try {
			cgi.exeScript(uri);
		}
		catch(std::exception &e)
    	{
			Error_page::send_error_page(server, request_map["path"], client_sock, 500, "Internal Server Error", location);
        	std::cerr << e.what() << std::endl;
    	}
		return;
	}
	else
		Error_page::send_error_page(server, request_map["path"], client_sock, 404, "Not Found", location);
}

void Cgi_request::result(int client_sock)
{
	std::ifstream in_file("temp.txt");
	if (in_file.is_open()) 
	{
		std::string fileContent((std::istreambuf_iterator<char>(in_file)), std::istreambuf_iterator<char>());
		std::string cont = "<html><body><h1>CGI executed</h1>"+fileContent+"</body></html>";
		std::stringstream ss;
		ss << cont.size();
		std::string content_length = ss.str();
		std::string response = "HTTP/1.1 200 OK\r\n";
		response += "Content-Type: text/html\r\n";
		response += "Content-Length: " + content_length + "\r\n";
		response += "\r\n";
		response += cont;
		in_file.close();
		int bytes_sent = write(client_sock, response.c_str(), response.size()+1);
		if (bytes_sent == -1) {
            perror("send failed");
            return;
        }
		remove("temp.txt");
		return;
	}
	else
	{
		std::string response = "HTTP/1.1 500 Internal Server Error\r\n";
		std::string cont = "<html><body><h1>CGI error</h1></body></html>";
		std::stringstream ss;
		ss << cont.size();
		std::string content_length = ss.str();
		response += "Content-Type: text/html\r\n";
		response += "Content-Length: " + content_length + "\r\n";
		response += "\r\n";
		response += cont;
		int bytes_sent = write(client_sock, response.c_str(), response.size()+1);
		if (bytes_sent == -1) {
            perror("send failed");
            return;
        }
		return;
	}
}